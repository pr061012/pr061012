/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

//TODO Add check whether object is visible

#include "HarmPerformer.h"
#include "../../../model/World/Object/Object.h"
#include "../../../model/BasicFuncs.h"

#include <vector>

HarmPerformer::HarmPerformer(Indexator &indexator):
    indexator(indexator)
{

}

HarmPerformer::~HarmPerformer()
{

}

void HarmPerformer::perform(Action& action)
{
    Object* actor = action.getActor();
    ObjectType type = actor -> getType();
    uint harm = randFromRange(0,100);

    if ((type != CREATURE) || (type != WEATHER))
    {
        action.markAsFailed();
    }
    else
    {
        std::vector<Object*> participants = action.getParticipants();

        for (int i = 0; i < participants.size(); i++)
        {
            participants[i].damage(harm);
        }
        action.markAsSucceeded();
    }
}
