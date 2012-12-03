/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cmath>
#include <string>

#include "EatingPerformer.h"
#include "../../../model/World/Object/Resource/Resource.h"
#include "../../../model/World/Object/Creatures/Creature.h"
#include "../../../common/BasicDefines.h"

// TODO
// Improve movement algo

EatingPerformer::EatingPerformer(World * world) :
    Performer(world)
{
}

EatingPerformer::~EatingPerformer()
{
}

void EatingPerformer::perform(Action& action)
{
    // Get needed data
    Object * actor = action.getActor();
    ObjectType actor_type = actor -> getType();

    // Check if actor is creature
    if (actor_type != CREATURE)
    {
        action.markAsFailed();
        action.setError(OBJ_CANT_EAT);
        return;
    }

    std::vector<Object*> participants = action.getParticipants();

    // check if there are more than one participants
    if (participants.size() > 1)
    {
        action.markAsFailed();
        action.setError(TOO_MANY_PARTICIPANTS);
        return;
    }

    Object * food = *(participants.begin());

    // check resource type
    if (food -> getType() != RESOURCE)
    {
        action.markAsFailed();
        action.setError(OBJ_IS_NOT_EATABLE);
        return;
    }

    // get food value
    uint food_value = 0;
    action.markAsPending();
    switch(dynamic_cast<Resource*>(food) -> getSubtype())
    {
        case RES_FOOD:
            food_value = 3;
            break;

        case GRASS:
            food_value = RES_BERRIES_FOOD_VALUE;
            break;

        case BERRIES:
            food_value = RES_GRASS_FOOD_VALUE;
            break;

        default:
            action.markAsFailed();
            break;
    }
    if (action.isFailed())
    {
        action.setError(OBJ_IS_NOT_EATABLE);
        return;
    }
     
    // check if an object lies in inventory or around object
    ObjectHeap * inventory = dynamic_cast<Creature*>(actor) -> getInventory();
    ObjectHeap surroundings = world -> getIndexator() -> 
                                getAreaContents(actor -> getShape());
    if (inventory -> find(food) != inventory -> end() ||
        surroundings.find(food) != surroundings.end())
    {
        // EPIC MEAL TIME!!!
        // TODO: Magic const.
        food -> damage(1);
        dynamic_cast<Creature*>(actor) -> decreaseHunger(food_value);
        action.markAsSucceeded();
        return;
    }


    action.markAsFailed();
}
