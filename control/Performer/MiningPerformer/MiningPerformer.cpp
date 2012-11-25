/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <vector>

#include "../../../model/World/Object/Creatures/Creature.h"
#include "../../../model/World/Object/Creatures/Humanoid/Humanoid.h"
#include "../../../model/World/Object/Tool/Tool.h"
#include "../../../model/World/Object/Resource/Resource.h"
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
/*
    uint tool_index = action.getParam<uint>("tool_index");
*/
    if ((actor -> getType() != CREATURE) && (participants.size() != 1))
    {
        action.markAsFailed();
        return;
    }

    Creature* creature = dynamic_cast<Creature*>(actor);
    CreatureType subtype = creature -> getSubtype();

    if (subtype == NON_HUMANOID)
    {
        action.markAsFailed();
        return;
    }

    Object* res = participants[res_index];
    // Object* tool = participant[tool_index];

    // Getting object is reach area.
    Shape reach_area = creature -> getReachArea();
    reach_area.setCenter(creature -> getCoords());
    ObjectHeap env = world -> getIndexator() -> getAreaContents(reach_area);

    // Trying to find required object.
    ObjectHeap::const_iterator iter = env.end();
    if (env.find(res, false) == iter)
    {
        action.markAsFailed();
        action.setError(OBJ_IS_OUT_OF_RANGE);
        return;
    }

    // Check whether resource is mineable.
    Resource* resource = dynamic_cast<Resource*>(res);
    if (!resource -> isMineable())
    {
        action.markAsFailed();
        action.setError(OBJ_IS_NOT_MINEABLE);
    }

    // Incrementing progress.
    resource -> incrementProgress();

    // Creating new resource object (if needed) and adding it to inventory.
    if (resource -> getProgress() == resource -> getDifficulty())
    {
        // Zeroing progress.
        resource -> setProgress(0);

        // Calculating drop amount.
        uint drop_amount = resource -> getAmountPerDrop();
        if (drop_amount > resource -> getAmount())
        {
            drop_amount = resource -> getAmount();
        }

        // Decreasing amount of resource.
        resource -> decreaseAmount(drop_amount);

        // Creating new resource.
        ParamArray pa;
        pa.addKey<ResourceType>("res_type", resource -> getSubtype());
        pa.addKey<uint>("res_amount", drop_amount);
        Resource* drop = dynamic_cast<Resource*>(this -> world -> getObjectFactory() -> createObject(RESOURCE, pa));

        // Making it only pickable.
        drop -> makePickable();

        // Adding object to inventory and world's heap.
        this -> world -> addObject(false, drop);
        dynamic_cast<Humanoid*>(creature) -> addToInventory(drop);
    }

    action.markAsSucceeded();
}
