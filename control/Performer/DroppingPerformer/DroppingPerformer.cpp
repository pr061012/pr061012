/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "DroppingPerformer.h"
#include "../../../model/Object/Creatures/Creature.h"
#include "../../../model/Object/Creatures/Humanoid/Humanoid.h"
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
        action.markAsFailed(OBJ_CANT_DROP);
        return;
    }
    else if (dynamic_cast<Creature*>(actor) -> getSubtype() != HUMANOID)
    {
        action.markAsFailed(OBJ_CANT_DROP);
        return;
    }

    // continue getting data
    std::vector<Object*> participants = action.getParticipants();
    Humanoid * human = dynamic_cast<Humanoid *>(actor);

    // initalize flags
    bool success = false;
    bool errors = false;
    ActionError act_error = NO_ERROR;
    std::vector<Object*> buffer;

    // go through all objects in participants and check if
    // they lie in inventory
    for (std::vector<Object*>::iterator j = participants.begin(); 
         j != participants.end(); j++) 
    {
        ObjectHeap::iterator object = human -> getInventory() -> find(*j);
        if (object == human -> getInventory() -> end())
        {
            errors = true;
            act_error = OBJ_IS_NOT_IN_HEAP;
        }
        else 
        {
            success = true;
            buffer.push_back(*j);
        }
    }
    
    // Move objects.
    for (std::vector<Object*>::iterator j = buffer.begin();
            j != buffer.end(); j++)
    {
        human -> removeFromInventory(*j);

        // make object visible
        world -> getVisibleObjects() -> push(*j);
        world -> getHiddenObjects() -> remove(*j);

        // place it on the ground
        (*j) -> setCoords(actor -> getCoords());
        world -> getIndexator() -> addObject(*j);
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
