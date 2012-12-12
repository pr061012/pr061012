/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <vector>

#include "../../../model/Object/Creatures/Creature.h"
#include "../../../model/Object/Creatures/Humanoid/Humanoid.h"
#include "../../../model/Object/Tool/Tool.h"
#include "../../../model/Object/Resource/Resource.h"
#include "../../../common/BasicDefines.h"

#include "MiningPerformer.h"

MiningPerformer::MiningPerformer(World * world):
    Performer(world)
{

}

MiningPerformer::~MiningPerformer()
{
}

void MiningPerformer::perform(Action& action)
{
    Object * actor = action.getActor();
    std::vector<Object*> participants = action.getParticipants();

    uint res_index = action.getParam<uint>("res_index");
    //uint tool_index = action.getParam<uint>("tool_index");

    // Only creature can mine.
    if ((actor -> getType() != CREATURE) ||
        (participants.size() != 1))
    {
        action.markAsFailed(OBJ_CANT_MINE);
        return;
    }
    else if(dynamic_cast<Creature*>(actor) -> getSubtype() != HUMANOID)
    { 
        action.markAsFailed(OBJ_CANT_MINE);
        return;
    }

    Humanoid* humanoid = dynamic_cast<Humanoid*>(actor);
    CreatureType subtype = humanoid -> getSubtype();

    // It's possible to mine only one object.
    if (participants.size() > 1)
    {
        action.markAsFailed(TOO_MANY_PARTICIPANTS);
        return;
    }

    Object* res = participants[res_index];
    // Object* tool = participant[tool_index];

    // Getting object is reach area.
    Shape reach_area = humanoid -> getReachArea();
    reach_area.setCenter(humanoid -> getCoords());
    ObjectHeap env = world -> getIndexator() -> getAreaContents(reach_area);

    // Trying to find required object.
    ObjectHeap::const_iterator iter = env.end();
    if (env.find(res, false) == iter)
    {
        action.markAsFailed(OBJ_IS_OUT_OF_RANGE);
        return;
    }

    // Check whether resource is mineable.
    Resource* resource = dynamic_cast<Resource*>(res);
    if (!resource -> isMineable())
    {
        action.markAsFailed(OBJ_IS_NOT_MINEABLE);
        return;
    }

    // Incrementing progress.
    resource -> incrementProgress();

    // Creating new resource object (if needed) and adding it to inventory.
    if (resource -> getProgress() == resource -> getDifficulty())
    {
        uint drop_amount = resource -> damage(resource -> getAmountPerDrop());
        // Creating new resource.
        ParamArray pa;
        pa.addKey<ResourceType>("res_type", resource -> getSubtype());
        pa.addKey<uint>("res_amount", drop_amount);
        Resource* drop = dynamic_cast<Resource*>(this -> world -> getObjectFactory() -> createObject(RESOURCE, pa));

        if (humanoid -> addToInventory(drop))
        {
            // Zeroing progress.
            resource -> setProgress(0);

            // Decreasing amount of resource.

            // Making it non-mineable and non-restorable.
            drop -> makeNonMineable();
            drop -> makeNonRestorable();

            // Adding object to inventory and world's heap.
            this -> world -> addObject(false, drop);
        }
        else
        {
            delete drop;
            resource -> heal(drop_amount);
            action.markAsFailed(NOT_ENOUGH_FREE_SPACE);
            return;
        }
    }

    action.markAsSucceeded();
}
