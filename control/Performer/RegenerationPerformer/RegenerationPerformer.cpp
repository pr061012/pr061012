/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "RegenerationPerformer.h"
#include "../../../common/Random/Random.h"
#include "../../../common/BasicDefines.h"

#include <vector>

RegenerationPerformer::RegenerationPerformer(Indexator& indexator):
    indexator(indexator)
{

}

RegenerationPerformer::~RegenerationPerformer()
{

}

void RegenerationPerformer::perform(Action& action)
{
    Object * actor = action.getActor();
    ObjectType type = actor -> getType();

    std::vector<Object*> participants = action.getParticipants();

    uint delta = Random::int_num(actor->getHealthPoints());

    uint object_index = action.getParam<uint>("object_index");
    uint tool_index = action.getParam<uint>("tool_index");

    ObjectHeap env = indexator.getAreaContents(actor->getShape());
    ObjectHeap::const_iterator iter = env.end();

    if ((type != RESOURCE) || (type != CREATURE))
    {
        action.markAsFailed();
        return;
    }

    if (env.find(participants[object_index], false) == iter)
    {
        action.markAsFailed();
        return;
    }

    if (object_index <= participants.size())
    {
        participants[object_index] -> heal(delta);
        action.markAsSucceeded();
    }
}
