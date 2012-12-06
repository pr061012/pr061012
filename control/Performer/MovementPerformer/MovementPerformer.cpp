/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

//**********************************************************
// TODO
// Add some check for distance between an actor and an object
//**********************************************************

#include "MovementPerformer.h"
#include "../../../model/World/Object/Resource/Resource.h"
#include "../../../model/World/Object/Creatures/Creature.h"
#include "../../../common/BasicDefines.h"
#include <cmath>
#include <string>

MovementPerformer::MovementPerformer(World * world) :
    Performer(world)
{
}

MovementPerformer::~MovementPerformer()
{
}

void MovementPerformer::perform(Action& action)
{
    // Get needed data
    Object * actor = action.getActor();
    ObjectType actor_type = actor -> getType();

    // check if actor can move objects
    if (actor_type != CREATURE && actor_type != WEATHER)
    {
        action.markAsFailed(OBJ_CANT_MOVE);
        return;
    }

    // check if actor tries to move only one object
    std::vector<Object*> participants = action.getParticipants();
    if (participants.size() != 1)
    {
        action.markAsFailed(TOO_MANY_PARTICIPANTS);
        return;
    }

    Object* participant = *participants.begin();

    // check if a participant can be moved
    if (!participant -> isMovable())
    {
        action.markAsFailed(OBJ_IS_NOT_MOVABLE);
        return;
    }

    // Get the area at which actor can move other objects.
    Shape reach_area;
    if (actor_type == WEATHER)
    {
        reach_area = actor -> getShape();
    }
    else
    {
        reach_area = dynamic_cast<Creature*>(actor) -> getReachArea();
        reach_area.setCenter(actor -> getCoords());
    }

    // Check if participant is inside reach area.
    if (!reach_area.hitTest(participant -> getShape()))
    {
        action.markAsFailed(OBJ_IS_OUT_OF_RANGE);
        return;
    }

    // continue getting data
    double angle = action.getParam<double>(std::string("angle"));
    SpeedType speed_type = action.getParam<SpeedType>(std::string("speed"));
    double speed = 0;
    switch (speed_type)
    {
        case SLOW_SPEED: 
            speed = CREAT_SPEED_SLOW_VALUE; 
        break;

        case FAST_SPEED:
            speed = CREAT_SPEED_FAST_VALUE;
        break;
    }
    
    Vector dest = participant -> getCoords() + Vector(speed * cos(angle), speed * sin(angle));

    // Do not let objects fall of the bounds
    if (dest.getX() < 0 || dest.getX() >= world -> getSize() || 
        dest.getY() < 0 || dest.getY() >= world -> getSize())
    {
        action.markAsFailed(NO_PLACE_TO_PLACE_OBJ_ON);
        return;
    }

    // Try to place an object and see if it collides with anything
    Shape ghost = participant -> getShape();
    ghost.setCenter(dest);
    ObjectHeap obstacles = world -> getIndexator() -> getAreaContents(ghost, 
                                                                      participant);
    action.markAsSucceeded();

    // Can't place things over creatures and buildings
    for (ObjectHeap::iterator i = obstacles.begin();
         i != obstacles.end(); i++)
    {
        if ((*i) -> isSolid() && !(*i) -> isCurrentlyFlying())
        {
            if ((*i) -> getShape().hitTest(ghost))
            {
                action.markAsFailed(NO_PLACE_TO_PLACE_OBJ_ON);
                return;
            }
        }
    }

    if (action.isSucceeded())
    {
        participant -> setCoords(dest);
        world -> getIndexator() -> reindexate(participant);
        action.markAsSucceeded();
    }
}
