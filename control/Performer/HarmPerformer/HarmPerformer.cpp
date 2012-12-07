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
#include "../../../model/World/Object/Creatures/Humanoid/Humanoid.h"

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
        Creature* cr = dynamic_cast<Creature*>(actor);
        env_shape = cr -> getReachArea();
        env_shape.setCenter(actor -> getCoords());
        for (uint i = 0; i < participants.size(); i++)
        {
            if (env_shape.hitTest(participants[i] -> getShape()))
            {
                uint harm = cr -> getForce() /
                            Random::int_range(DMG_FORCE_MIN, DMG_FORCE_MAX);
                participants[i] -> damage(harm);

                // Send message about attack.
                Message msg(UNDER_ATTACK, actor);
                participants[i] -> receiveMessage(msg);
                if
                (
                    (participants[i] -> getHealthPoints() == 0) &&
                    (participants[i] -> getType() == CREATURE) &&
                    (actor -> getType() == CREATURE)
                )
                {
                    Creature* cr = dynamic_cast<Creature*>(participants[i]);
                    Creature* cr_actor = dynamic_cast<Creature*>(actor);
                    if (cr_actor -> getSubtype() == HUMANOID)
                    {
                        Humanoid* hum = dynamic_cast<Humanoid*>(cr_actor);

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
    }

    else if (type == WEATHER)
    {
        Weather* weather = dynamic_cast<Weather*>(actor);
        env_shape = weather -> getShape();

        for (uint i = 0; i < participants.size(); i++)
        {
            if (env_shape.hitTest(participants[i] -> getShape()))
            {
                uint harm = weather -> getDangerLevel() /
                            Random::int_range(DMG_DANGER_MIN, DMG_DANGER_MAX);
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
        return;
    }
    // If all objects are out of reach, then...
    else if (count_error == participants.size())
    {
        action.markAsFailed(ALL_OBJS_ARE_OUT_OF_REACH);
        return;
    }
    // If some objects are out of reach, then...
    else
    {
        action.markAsSucceededWithErrors(SOME_OBJS_ARE_OUT_OF_REACH);
    }
}
