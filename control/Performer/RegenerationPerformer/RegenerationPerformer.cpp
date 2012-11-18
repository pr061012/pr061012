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

}
