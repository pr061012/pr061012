/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cmath>
#include <string>

#include "MovementPerformer.h"
#include "../../../common/BasicDefines.h"

MovementPerformer::MovementPerformer(const double world_size, 
                                     Indexator* indexator) :
    world_size(world_size), indexator(indexator)
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

    // check if actor can go
    if (actor_type != CREATURE && actor_type != WEATHER)
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
    Point dest = actor -> getCoords() + Point(speed * cos(angle), speed * sin(angle));

    // Do not let objects fall of the bounds
    if (dest.getX() < 0 || dest.getX() >= world_size || 
        dest.getY() < 0 || dest.getY() >= world_size)
    {
        action.markAsFailed();
        return;
    }

    // Try to place an object and see if it collides with anything
    Shape ghost = actor -> getShape();
    ghost.setCenter(dest);
    ObjectHeap obstacles = indexator -> getAreaContents(ghost);

    // Nothing can stop weather, and creature can't stop itself
    if (actor -> getType() == WEATHER || 
        ((obstacles.getTypeAmount(CREATURE) == 1 && *obstacles.begin() == actor
         || !obstacles.getTypeAmount(CREATURE))
        && !obstacles.getTypeAmount(BUILDING)))
    {
        actor -> setCoords(dest);
        indexator -> reindexate(actor);
        action.markAsSucceeded();
    }
    else
    {
        action.markAsFailed();
    }
}
