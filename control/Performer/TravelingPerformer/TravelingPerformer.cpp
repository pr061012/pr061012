/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cmath>
#include <string>

#include "TravelingPerformer.h"
#include "../../../common/BasicDefines.h"
#include "../../../common/Log/Log.h"

TravelingPerformer::TravelingPerformer(const double world_size, 
                                     Indexator* indexator) :
    world_size(world_size), indexator(indexator)
{
}

TravelingPerformer::~TravelingPerformer()
{
}

void TravelingPerformer::perform(Action& action)
{
    // Get needed data
    Object * actor = action.getActor();
    ObjectType actor_type = actor -> getType();

    // check if actor can go
    if (actor_type != CREATURE && actor_type != WEATHER)
    {
        action.markAsFailed();
        action.setError(OBJ_IS_NOT_MOVEABLE);
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
    Vector origin = actor -> getCoords();
    Vector dest = origin + Vector(speed * cos(angle), speed * sin(angle));

    // Do not let objects fall of the bounds
    if (dest.getX() < 0 || dest.getX() >= world_size || 
        dest.getY() < 0 || dest.getY() >= world_size)
    {
        action.markAsFailed();
        action.setError(OBJ_IS_OUT_OF_RANGE);
        return;
    }

    // Try to place an object and see if it collides with anything
    actor -> setCoords(dest);
    ObjectHeap obstacles = indexator -> getAreaContents(actor -> getShape());

    // Nothing can stop weather, and creature can't stop itself
    if (actor -> getType() == WEATHER || 
        (actor -> getType() == CREATURE && obstacles.getTypeAmount(CREATURE) == 1 
        && *obstacles.begin() == actor
        && !obstacles.getTypeAmount(BUILDING)))
    {
        //Log::NOTE(std::to_string(obstacles.getTypeAmount(CREATURE)));
        indexator -> reindexate(actor);
        action.markAsSucceeded();
    }
    else
    {
        actor -> setCoords(origin);
        action.setError(OBJ_IS_STUCK);
        action.markAsFailed();
    }
}
