/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cmath>
#include <string>

#include "TravelingPerformer.h"
#include "../../../common/BasicDefines.h"
#include "../../../common/Log/Log.h"

TravelingPerformer::TravelingPerformer(World * world) :
    Performer(world)
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
    if (dest.getX() < 0 || dest.getX() >= world -> getSize() || 
        dest.getY() < 0 || dest.getY() >= world -> getSize())
    {
        action.markAsFailed();
        action.setError(OBJ_IS_OUT_OF_RANGE);
        return;
    }

    // place an object
    actor -> setCoords(dest);

    // Nothing can stop weather
    if (actor -> getType() == WEATHER)
    {
        action.markAsSucceeded();
        world -> getIndexator() -> reindexate(actor);
        return;
    }
    else
    {
        action.markAsSucceeded();

        // Look for all the obstacles and check if actor collides
        // with anything
        ObjectHeap obstacles = world -> getIndexator() -> getAreaContents(actor -> getShape());
        for (ObjectHeap::iterator i = obstacles.begin();
             i != obstacles.end(); i++)
        {
            if ((*i) -> isSolid() && (*i) != actor)
            {
                action.markAsFailed();
                break;
            }
        }

        // if everything is ok, reindexate actor
        if (!action.isFailed())
        {
            world -> getIndexator() -> reindexate(actor);
            return;
        }

    }

    // roll back if something wrong
    actor -> setCoords(origin);
    action.setError(OBJ_IS_STUCK);
    action.markAsFailed();
}
