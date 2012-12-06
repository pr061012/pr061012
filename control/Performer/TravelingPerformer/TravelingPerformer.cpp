/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cmath>
#include <string>

#include "TravelingPerformer.h"
#include "../../../model/World/Object/Creatures/Creature.h"
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
    Object* actor = action.getActor();
    ObjectType actor_type = actor -> getType();

    // check if actor can go
    if (!actor -> isMovable())
    {
        action.markAsFailed(OBJ_IS_NOT_MOVABLE);
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
            // If actor is creature, it can't run with 0 endurance.
            if (actor -> getType() == CREATURE)
            {
                if (dynamic_cast<Creature*>(actor) -> getEndurance() > 0)
                {
                    speed = CREAT_SPEED_FAST_VALUE;
                }
                else
                {
                    speed = CREAT_SPEED_SLOW_VALUE;
                }
            }
            else
            {
                speed = CREAT_SPEED_SLOW_VALUE;
            }
            break;

    }
    Vector origin = actor -> getCoords();
    Vector dest = origin + Vector(speed * cos(angle), speed * sin(angle));
    double size = actor -> getShape().getSize() / 2;
    // Do not let objects fall of the bounds
    if
    (
        dest.getX() - size < 0 ||
        dest.getX() + size >= world -> getSize() ||
        dest.getY() - size < 0 ||
        dest.getY() + size >= world -> getSize()
    )
    {
        // FIXME: Strange error, isn't it?
        action.markAsFailed(OBJ_IS_OUT_OF_WORLD_BOUNDS);
        return;
    }

    // place an object
    actor -> setCoords(dest);

    // Nothing can stop non-solid and flying objects
    if (!actor -> isSolid() || actor -> isCurrentlyFlying())
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
                action.markAsFailed(NO_PLACE_TO_PLACE_OBJ_ON);
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
}
