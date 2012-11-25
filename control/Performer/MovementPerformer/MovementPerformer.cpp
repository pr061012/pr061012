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
        action.markAsFailed();
        return;
    }

    // check if actor tries to move only one object
    std::vector<Object*> participants = action.getParticipants();
    if (participants.size() != 1)
    {
        action.markAsFailed();
        return;
    }

    Object * participant = *participants.begin();

    // check if a participant can be moved (tools and mined resources)
    if
    (
        participant -> getType() != TOOL &&
        !(participant -> getType() == RESOURCE &&
        !dynamic_cast<Resource*>(participant) -> isMineable())
    )
    {
        action.markAsFailed();
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
        action.markAsFailed();
        return;
    }

    // Try to place an object and see if it collides with anything
    Shape ghost = participant -> getShape();
    ghost.setCenter(dest);
    ObjectHeap obstacles = world -> getIndexator() -> getAreaContents(ghost);

    // Can't place things over creatures and buildings
    if (!obstacles.getTypeAmount(CREATURE)
        && !obstacles.getTypeAmount(BUILDING))
    {
        participant -> setCoords(dest);
        world -> getIndexator() -> reindexate(participant);
        action.markAsSucceeded();
    }
    else
    {
        action.markAsFailed();
    }
}
