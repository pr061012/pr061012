/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "PickupMaster.h"
#include "../../../model/World/Object/Creatures/Creature.h"
#include "../../../model/World/Object/Creatures/Humanoid/Humanoid.h"
#include <string>
#include <cmath>

PickupMaster::PickupMaster(World * world) :
    Performer(world)
{
}

PickupMaster::~PickupMaster()
{
}

void PickupMaster::perform(Action& action)
{
    // Get needed data
    Object * actor = action.getActor();
    ObjectType actor_type = actor -> getType();

    // check if actor can pick up
    if (actor_type != CREATURE)
    {
        action.markAsFailed();
    }
    else if(dynamic_cast<Creature*>(actor) -> getSubtype() != HUMANOID)
    { 
        action.markAsFailed();
    }

    if (action.isFailed())
    {
        action.setError(OBJ_CANT_PICKUP);
        return;
    }
    // continue getting data
    Vector dest = actor -> getCoords();
    std::vector<Object*> participants = action.getParticipants();
    ObjectHeap * inventory = dynamic_cast<Humanoid *>(actor) -> getInventory();

    //*************************************************************************
    // TODO
    // check if creature can have enough place to pickup
    //*************************************************************************
    bool errors = false;
    bool success = false;
    // go through all objects in participants and put them in inventory
    for (std::vector<Object*>::iterator j = participants.begin();
            j != participants.end(); j++) 
    {
        if ((*j) -> getType() != RESOURCE &&
            (*j) -> getType() != TOOL) 
        {
            errors = true;
            action.setError(OBJ_IS_NOT_PICKABLE);
        }
        else
        {
            // make object hidden
            world -> getVisibleObjects() -> remove(*j);
            world -> getHiddenObjects() -> push(*j);
            world -> getIndexator() -> removeObject(*j);

            // put it in inventory
            inventory -> push(*j);

            // remove from index
            success = true;
        }
    }

    if (!success)
    {
        action.markAsFailed();
    }
    else if (success && errors) 
    {
        action.markAsSucceededWithErrors();
    }
    else 
    {
        action.markAsSucceeded();
    }
}
