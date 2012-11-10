/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "HarmPerformer.h"


HarmPerformer::HarmPerformer()
{

}

HarmPerformer::~HarmPerformer()
{

}

void HarmPerformer::perform(Action& action)
{
    Object* actor = action.getActor();
    ObjectType type = actor -> getType();

    if ((type != CREATURE) || (type != WEATHER))
    {
        action.markAsFailed();
    }
    else
    {
        action.markAsSucceeded();
    }
}
