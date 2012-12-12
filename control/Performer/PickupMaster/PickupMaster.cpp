/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "PickupMaster.h"
#include "../../../model/Object/Creatures/Creature.h"
#include "../../../model/Object/Creatures/Humanoid/Humanoid.h"
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
    Object* actor = action.getActor();
    ObjectType actor_type = actor -> getType();

    // check if actor can pick up
    if (actor_type != CREATURE)
    {
        action.markAsFailed(OBJ_CANT_PICKUP);
        return;
    }
    else if(dynamic_cast<Creature*>(actor) -> getSubtype() != HUMANOID)
    { 
        action.markAsFailed(OBJ_CANT_PICKUP);
        return;
    }

    // continue getting data
    Vector dest = actor -> getCoords();
    std::vector<Object*> participants = action.getParticipants();
    Humanoid * human = dynamic_cast<Humanoid *>(actor);

    bool errors = false;
    bool success = false;
    ActionError act_error = NO_ERROR;

    // go through all objects in participants and put them in inventory
    for (std::vector<Object*>::iterator j = participants.begin();
            j != participants.end(); j++) 
    {
        // Check if object is pickable.
        if (!(*j) -> isPickable()) 
        {
            errors = true;
            act_error = OBJ_IS_NOT_PICKABLE;
        }
        // Check if an object fits in the inventory.
        else if (human -> addToInventory(*j))
        {
            // make object hidden
            world -> getVisibleObjects() -> remove(*j);
            world -> getHiddenObjects() -> push(*j);
            world -> getIndexator() -> removeObject(*j);
            success = true;
        }
        else
        {
            errors = true;
            act_error = NOT_ENOUGH_FREE_SPACE;
        }
    }

    if (!success)
    {
        action.markAsFailed(act_error);
    }
    else if (success && errors) 
    {
        action.markAsSucceededWithErrors(act_error);
    }
    else 
    {
        action.markAsSucceeded();
    }
}
