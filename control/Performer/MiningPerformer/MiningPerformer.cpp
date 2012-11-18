/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "MiningPerformer.h"


MiningPerformer::MiningPerformer(Indexator &indexator):
    indexator(indexator)
{

}

MiningPerformer::~MiningPerformer()
{
}

void MiningPerformer::perform(Action& action)
{
    Object * actor = action.getActor();
    int res_id = action.getParam<int>("res_id");
    int tool_id = action.getParam<int>("tool_id");

    if (actor -> getType() != CREATURE)
    {
        action.markAsFailed();
    }
    else
    {

    }

}
