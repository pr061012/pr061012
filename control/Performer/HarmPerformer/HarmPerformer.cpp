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
#include "../../../model/World/Object/Weather/Weather.h"
#include "../../../model/World/Object/Creatures/Humanoid/Humanoid.h"
#include "../../../model/World/Object/Creatures/NonHumanoid/NonHumanoid.h"

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
    // Random))
    if (Random::int_range(0, 100) > 90)
    {
        return;
    }
    // Get actor and type of actor.
    Object* actor = action.getActor();
    ObjectType type = actor -> getType();
    uint harm = calculateHarm(actor);

    uint count_error = 0;
    // Check type of actor.
    if ((type != CREATURE) && (type != WEATHER))
    {
        action.markAsFailed(OBJ_CANT_HARM);
        return;
    }

    // Get participants of action.
    std::vector<Object*> participants = action.getParticipants();

    // Get shape influence.
    Shape env_shape;
    if (type == CREATURE)
    {
        if (participants.size() != 1)
        {
            action.markAsFailed(TOO_MANY_PARTICIPANTS);
            return;
        }

        if (participants[0] -> isImmortal())
        {
            action.markAsFailed(OBJ_IS_IMMORTAL);
            return;
        }

        Creature* actor_cr = dynamic_cast<Creature*>(actor);
        env_shape = actor_cr -> getReachArea();
        env_shape.setCenter(actor_cr -> getCoords());

        if (env_shape.hitTest(participants[0] -> getShape()))
        {
            participants[0] -> damage(harm);

            // Send message about attack.
            Message msg(UNDER_ATTACK, actor_cr);
            participants[0] -> receiveMessage(msg);
            if
            (
                (participants[0] -> getHealthPoints() == 0) &&
                (participants[0] -> getType() == CREATURE)
            )
            {
                Creature* cr = dynamic_cast<Creature*>(participants[0]);
                if (actor_cr -> getSubtype() == HUMANOID)
                {
                    Humanoid* hum = dynamic_cast<Humanoid*>(actor_cr);

                    ObjectHeap* drop = cr -> getDropObjects();
                    ObjectHeap::iterator iter;
                    for(iter = drop -> begin(); iter != drop -> end(); iter++)
                    {
                        hum -> addToInventory(*iter);
                    }
                    drop -> clear();
                }
            }
        }
        else
        {
            // Count the amount of error.
            count_error += 1;
        }
    }

    else if (type == WEATHER)
    {
        Weather* weather = dynamic_cast<Weather*>(actor);
        env_shape = weather -> getShape();

        for (uint i = 0; i < participants.size(); i++)
        {
            if
            (
                env_shape.hitTest(participants[i] -> getShape()) &&
                !participants[i] -> isImmortal()
            )
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

    }

    // If all objects receive attack, then...
    if (!count_error)
    {
        action.markAsSucceeded();
    }
    // If all objects are out of reach, then...
    else if (count_error == participants.size())
    {
        // FIXME: Setting this error even if error is in immortal objects.
        action.markAsFailed(ALL_OBJS_ARE_OUT_OF_REACH);
    }
    // If some objects are out of reach, then...
    else
    {
        // FIXME: Setting this error even if error is in immortal objects.
        action.markAsSucceededWithErrors(SOME_OBJS_ARE_OUT_OF_REACH);
    }
}


uint HarmPerformer::calculateHarm(Object* actor)
{
    ObjectType type = actor -> getType();
    if (type == CREATURE)
    {
        Creature* cr = dynamic_cast<Creature*>(actor);
        CreatureType subtype = cr -> getSubtype();
        uint force = cr -> getForce();

        if (subtype == HUMANOID)
        {
            return force * Random::int_range(DMG_HUM_MIN, DMG_HUM_MAX);
        }
        else
        {
            NonHumanoid* nhum = dynamic_cast<NonHumanoid*>(cr);
            NonHumanoidType sstype = nhum -> getSubsubtype();

            if (sstype == DRAGON)
            {
                return force * Random::int_range(DMG_NHUM_DRG_MIN, DMG_NHUM_DRG_MAX);
            }
            else if (sstype == COW)
            {
                return force * Random::int_range(DMG_NHUM_COW_MIN, DMG_NHUM_COW_MAX);
            }
            else
            {
                return force * Random::int_range(DMG_NHUM_MIN, DMG_NHUM_MAX);
            }
        }
    }
    else if (type == WEATHER)
    {
        Weather* weat = dynamic_cast<Weather*>(actor);
        WeatherType type = weat -> getSubtype();

        if (type == HURRICANE)
        {
            return Random::int_range(DMG_WEAT_HRCN_MIN, DMG_WEAT_HRCN_MAX);
        }
        else if (type == METEOR_SHOWER)
        {
            return Random::int_range(DMG_WEAT_MS_MIN, DMG_WEAT_MS_MAX);
        }
        else
        {
            return Random::int_range(DMG_WEAT_MIN, DMG_WEAT_MAX);
        }
    }
    else
    {
        return 0;
    }
}
