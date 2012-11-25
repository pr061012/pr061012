/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "PickupMaster.h"
#include "../../../model/World/Object/Creatures/Creature.h"
#include <string>
#include <cmath>

//*****************************************************************************
// FOR TEST ONLY
//*****************************************************************************
#ifndef CREAT_SPEED_FAST_VALUE
#define CREAT_SPEED_FAST_VALUE 10
#endif

#ifndef CREAT_SPEED_SLOW_VALUE
#define CREAT_SPEED_SLOW_VALUE 5
#endif

PickupMaster::PickupMaster(World * world, ObjectHeap * buffer) :
    Performer(world),
    buffer(buffer)
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
        action.setError(OBJ_CANT_PICKUP);
        return;
    }

    // continue getting data
    Vector dest = actor -> getCoords();
    std::vector<Object*> participants = action.getParticipants();
    ObjectHeap * inventory = dynamic_cast<Creature *>(actor) -> getInventory();

    //*************************************************************************
    // TODO
    // check if creature can have enough place to pickup
    //*************************************************************************
    bool errors = false;
    bool success = false;
    // go through all objects in participants and put them in inventory
    for (ObjectHeap::iterator j = participants.begin(); 
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
            buffer -> push(*j);
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
