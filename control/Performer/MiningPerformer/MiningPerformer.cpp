/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "MiningPerformer.h"
#include "../../../model/World/Object/Creatures/Creature.h"
#include "../../../model/World/Object/Tool/Tool.h"
#include "../../../model/World/Object/Resource/Resource.h"

#include <vector>

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

    ObjectHeap env = world -> getIndexator() -> getAreaContents(creature -> getViewArea());
    Object* res = participants[res_index];
/*
    Object* tool = participant[tool_index];
*/
    ObjectHeap::const_iterator iter = env.end();

    if (env.find(res, false) == iter)
    {
        action.markAsFailed();
        return;
    }

    dynamic_cast<Resource*>(res) -> incrementProgress();

    action.markAsSucceeded();
}
