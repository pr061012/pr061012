/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "RegenerationPerformer.h"
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
    std::vector<Object*> participants = action.getParticipants();

    ObjectType type = actor -> getType();
    uint object_index = action.getParam<uint>("object_index");

    ObjectHeap env = indexator.getAreaContents(actor->getShape());
    ObjectHeap::const_iterator iter = obstacles.end();

    if ((type != RESOURCE) || (type != CREATURE))
    {

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
