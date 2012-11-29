/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "HarmPerformer.h"

#include "../../../common/Math/Random.h"
#include "../../../common/BasicDefines.h"
#include "../../../common/BasicTypes.h"

#include "../../../model/World/Message/Message.h"
#include "../../../model/World/Object/Object.h"
#include "../../../model/World/Object/Creatures/Creature.h"
#include "../../../model/World/Object/Weather/Weather.h"

#include <vector>

HarmPerformer::HarmPerformer(World* world):
    Performer(world)
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
    if ((type != CREATURE) && (type != WEATHER))
    {
        action.setError(OBJ_CANT_HARM);
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
        env_shape = cr -> getReachArea();
    }

    if (type == WEATHER)
    {
        Weather* weather = dynamic_cast<Weather*>(actor);
        env_shape = weather -> getShape();
    }

    // Harm object in view area.
    uint count_error = 0;
    for (uint i = 0; i < participants.size(); i++)
    {
        if (env_shape.hitTest(participants[i] -> getShape()))
        {
            participants[i] -> damage(harm);

            // Send message about attack.
            Message msg(UNDER_ATTACK, actor);
            participants[i] -> receiveMessage(msg);
        }
        else
        {
            // Count the amount of error.
            count_error += 1;
        }
    }

    // If all objects receive attack, then...
    if (!count_error)
    {
        action.markAsSucceeded();
        return;
    }
    // If all objects are out of reach, then...
    else if (count_error == participants.size())
    {
        action.setError(ALL_OBJS_ARE_OUT_OF_REACH);
        action.markAsFailed();
        return;
    }
    // If some objects are out of reach, then...
    else
    {
        action.setError(SOME_OBJS_ARE_OUT_OF_REACH);
        action.markAsSucceededWithErrors();
    }
}
