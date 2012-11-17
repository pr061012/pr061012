/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "HarmPerformer.h"
#include "../../../model/World/Object/Object.h"
#include "../../../common/Random/Random.h"
#include "../../../common/BasicDefines.h"
#include "../../../common/BasicTypes.h"

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
    uint harm = Random::int_num(actor -> getDangerLevel());

    ObjectHeap obstacles = indexator.getAreaContents(actor -> getShape());
    ObjectHeap::const_iterator iter = obstacles.end();
    uint count_error = 0;
    if (type != CREATURE)
    {
        action.markAsFailed();
    }
    else
    {
        std::vector<Object*> participants = action.getParticipants();

        for (uint i = 0; i < participants.size(); i++)
        {
            if (obstacles.find(participants[i], false) != iter)
            {
                participants[i] -> damage(harm);
            }
            else
            {
                ActionError error = OBJ_IS_OUT_OF_VIEW;
                action.setError(error);
                count_error += 1;
            }
        }
        if (!count_error)
        {
            action.markAsSucceeded();
        }
        else
        {
            action.markAsSucceededWithErrors();
        }
    }
}
