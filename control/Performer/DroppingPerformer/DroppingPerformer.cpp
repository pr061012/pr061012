/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "DroppingPerformer.h"
#include "../../../model/World/Object/Creatures/Creature.h"
#include "../../../model/World/Object/Creatures/Humanoid/Humanoid.h"
#include <string>
#include <cmath>

DroppingPerformer::DroppingPerformer(World * world) :
    Performer(world)
{
}

DroppingPerformer::~DroppingPerformer()
{
}

void DroppingPerformer::perform(Action& action)
{
    // Get needed data
    Object * actor = action.getActor();
    ObjectType actor_type = actor -> getType();

    // check if actor can drop
    if (actor_type != CREATURE)
    {
        action.markAsFailed();
    }
    else if (dynamic_cast<Creature*>(actor) -> getSubtype() != HUMANOID)
    {
        action.markAsFailed();
    }

    if (action.isFailed())
    {
        action.setError(OBJ_CANT_DROP);
        return;
    }

    // continue getting data
    std::vector<Object*> participants = action.getParticipants();
    ObjectHeap * inventory = dynamic_cast<Humanoid *>(actor) -> getInventory();

    // initalize flags
    bool success = false;
    bool errors = false;

    // go through all objects in participants and check if
    // they lie in inventory
    for (std::vector<Object*>::iterator j = participants.begin(); 
         j != participants.end(); j++) 
    {
        ObjectHeap::iterator object = inventory -> find(*j);
        if (object == inventory -> end())
        {
            errors = true;
            action.setError(OBJ_IS_NOT_IN_HEAP);
        }
        else 
        {
            success = true;

            // make object visible
            world -> getVisibleObjects() -> push(*j);
            world -> getHiddenObjects() -> remove(*j);

            // place it on the ground
            inventory -> remove(*j);
            (*j) -> setCoords(actor -> getCoords());

            world -> getIndexator() -> addObject(*j);
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
