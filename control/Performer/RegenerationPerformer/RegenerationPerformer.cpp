/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "RegenerationPerformer.h"
#include "../../../common/Math/Random.h"
#include "../../../common/BasicDefines.h"
#include "../../../model/World/Object/Creatures/Creature.h"
#include "../../../model/World/Object/Object.h"
#include "../../../model/World/Object/Resource/Resource.h"

#include <vector>

RegenerationPerformer::RegenerationPerformer(World * world):
    Performer(world)
{

}

RegenerationPerformer::~RegenerationPerformer()
{

}

void RegenerationPerformer::perform(Action& action)
{
    Object* actor = action.getActor();
    ObjectType type = actor -> getType();
    std::vector<Object*> participants = action.getParticipants();

    uint delta = Random::int_num(actor -> getHealthPoints());

    uint object_index = action.getParam<uint>("object_index");
    // uint tool_index = action.getParam<uint>("tool_index");

    if (object_index > participants.size())
    {
        action.markAsFailed();
        return;
    }

    if ((type != RESOURCE) && (type != CREATURE))
    {
        action.markAsFailed();
        return;
    }

    if (type == RESOURCE)
    {
        if (actor == participants[object_index])
        {
            actor -> heal(delta);
            action.markAsSucceeded();
            return;
        }
        else
        {
            action.markAsFailed();
            return;
        }
    }

    if (type == CREATURE)
    {
        Creature* creature = dynamic_cast<Creature*>(actor);
        if (creature -> getSubtype() == NON_HUMANOID)
        {
            action.markAsFailed();
            return;
        }
        Shape reach_area = creature -> getReachArea();
        reach_area.setCenter(creature -> getCoords());
        ObjectHeap env = world -> getIndexator() -> getAreaContents(reach_area);
        ObjectHeap::const_iterator iter;
        ObjectHeap* inventory = creature -> getInventory();
        uint count = 0;
        for
        (
            iter = inventory -> begin(RESOURCE);
            iter != inventory -> end(RESOURCE); iter++
        )
        {
            Resource* res = dynamic_cast<Resource*>(*iter);
            res -> decreaseAmount(1);
            count++;
        }
        if (count == 0)
        {
            action.markAsFailed();
            return;
        }

        iter = env.end();
        if (env.find(participants[object_index], false) == iter)
        {
            action.markAsFailed();
            return;
        }
        else
        {
            participants[object_index] -> heal(delta * count);
            action.markAsSucceeded();
        }
    }
}
