/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "HarmPerformer.h"
#include "../../../model/World/Object/Object.h"
#include "../../../common/Random/Random.h"
#include "../../../common/BasicDefines.h"
#include "../../../common/BasicTypes.h"
#include "../../../model/World/Object/Creatures/Creature.h"
#include "../../../model/World/Object/Weather/Weather.h"

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
    // Get actor and type of actor.
    Object* actor = action.getActor();
    ObjectType type = actor -> getType();

    // Set damage.
    uint harm = Random::int_range(DMG_PER_HIT_MIN, DMG_PER_HIT_MAX);
    harm *= actor -> getDangerLevel();

    // Check type of actor.
    if ((type != CREATURE) || (type != WEATHER))
    {
        action.markAsFailed();
        return;
    }

    // Get participants of action.
    std::vector<Object*> participants = action.getParticipants();

    // Get shape influence.
    Shape env_shape;
    if (type == CREATURE)
    {
        Creature* cr = dynamic_cast<Creature*>(actor);
        env_shape = cr -> getViewArea();
    }

    if (type == WEATHER)
    {
        Weather* weather = dynamic_cast<Weather*>(actor);
        env_shape = weather -> getShape();
    }

    // Get area contents of actor.
    ObjectHeap obstacles = indexator.getAreaContents(env_shape);
    ObjectHeap::const_iterator iter = obstacles.end();

    // Harm object in view area.
    uint count_error = 0;
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
        return;
    }
    if (count_error == participants.size())
    {
        action.markAsFailed();
        return;
    }
    else
    {
        action.markAsSucceededWithErrors();
    }
}
