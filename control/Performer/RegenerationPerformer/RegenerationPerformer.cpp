/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "RegenerationPerformer.h"
#include "../../../common/Math/Random.h"
#include "../../../common/BasicDefines.h"
#include "../../../model/Object/Creatures/Creature.h"
#include "../../../model/Object/Creatures/Humanoid/Humanoid.h"
#include "../../../model/Object/Object.h"
#include "../../../model/Object/Resource/Resource.h"
#include "../../../model/Object/Weather/Weather.h"

#include <vector>

RegenerationPerformer::RegenerationPerformer(World * world):
    Performer(world)
{

}

RegenerationPerformer::~RegenerationPerformer()
{

}

void RegenerationPerformer::perform(Action& action)
{
    Object* actor = action.getActor();
    ObjectType type = actor -> getType();
    std::vector<Object*> participants = action.getParticipants();

    uint object_index = action.getParam<uint>("object_index");
    // uint tool_index = action.getParam<uint>("tool_index");

    if (object_index >= participants.size())
    {
        action.markAsFailed(INCORRECT_INDEX);
        return;
    }

    if ((type != RESOURCE) && (type != CREATURE) && (type != WEATHER))
    {
        action.markAsFailed(OBJ_CANT_REGENERATE);
        return;
    }

    if (type == RESOURCE)
    {
        if (actor == participants[object_index])
        {
            uint delta = dynamic_cast<Resource*>(actor) -> getRegAmount();
            actor -> heal(delta);
            action.markAsSucceeded();
            return;
        }
        else
        {
            action.markAsFailed(OBJ_CAN_REGENERATE_ONLY_ITSELF);
            return;
        }
    }

    else if (type == CREATURE)
    {
        if (dynamic_cast<Creature*>(actor) -> getSubtype() == HUMANOID)
        {
            Humanoid* humanoid = dynamic_cast<Humanoid*>(actor);

            if (participants[object_index] -> getType() != BUILDING)
            {
                action.markAsFailed(OBJ_IS_NOT_REGENERABLE);
                return;
            }
            if (humanoid -> getSubtype() == NON_HUMANOID)
            {
                action.markAsFailed(OBJ_CANT_REGENERATE);
                return;
            }

            Building* building = dynamic_cast<Building*>(participants[object_index]);
            // Check whether humanoid can heal this object.
            Shape reach_area = humanoid -> getReachArea();
            reach_area.setCenter(humanoid -> getCoords());
            if (!reach_area.hitTest(building -> getShape()))
            {
                action.markAsFailed(ALL_OBJS_ARE_OUT_OF_REACH);
                return;
            }

            uint rest_hp = building -> getMaxHealthPoints() - building -> getHealthPoints();

            // Searching for objects.
            ObjectHeap* inventory = humanoid -> getInventory();
            ObjectHeap::const_iterator iter;
            uint count = 0;

            for
            (
                iter = inventory -> begin(RESOURCE);
                iter != inventory -> end(RESOURCE);
                iter++
            )
            {
                Resource* res = dynamic_cast<Resource*>(*iter);
                if (res -> getSubtype() != TREE)
                {
                    continue;
                }
                while ((rest_hp > count) && (res -> getHealthPoints() != 0))
                {
                    if (rest_hp < count + REG_BUILDING_COEF)
                    {
                        count = rest_hp;
                        res -> damage(1);
                    }
                    else
                    {
                        res -> damage(1);
                        count += REG_BUILDING_COEF;
                    }
                }
            }
            if (count == 0)
            {
                action.markAsFailed(NOT_ENOUGH_INGREDIENTS);
                return;
            }

            building -> heal(count);
            action.markAsSucceeded();
        }
    }
    else if (type == WEATHER)
    {
        uint count_error = 0;
        Weather* weat = dynamic_cast<Weather*>(actor);
        Shape env_shape = weat -> getShape();
        env_shape.setCenter(weat -> getCoords());

        for (uint i = 0; i < participants.size(); i++)
        {
            if (!env_shape.hitTest(participants[i] -> getShape()))
            {
                count_error++;
            }
            else
            {
                if (participants[i] -> getType() == RESOURCE)
                {
                    participants[i] -> heal(REG_RES_COEF);
                }
                else
                {
                    count_error++;
                }
            }
        }
        if (!count_error)
        {
            action.markAsSucceeded();
            return;
        }
        if (count_error == participants.size())
        {
            action.markAsFailed(ALL_OBJS_ARE_OUT_OF_REACH);
            return;
        }
        else
        {
            action.markAsSucceededWithErrors(SOME_OBJS_ARE_OUT_OF_REACH);
            return;
        }
    }
}
