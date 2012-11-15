/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "RegenerationPerformer.h"

RegenerationPerformer::RegenerationPerformer()
{

}

RegenerationPerformer::~RegenerationPerformer()
{

}

void RegenerationPerformer::perform(Action& action)
{
    Object * actor = action.getActor();
    int building_id = action.getParam<uint>("building_id");
    int tool_id = action.getParam<uint>("tool_id");

    if (actor -> getType() != CREATURE)
    {
        action.markAsFailed();
    }
}
