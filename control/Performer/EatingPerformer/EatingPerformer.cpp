/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "EatingPerformer.h"
#include "../../../model/World/Object/Resource/Resource.h"
#include "../../../model/World/Object/Creatures/Creature.h"
#include "../../../model/BasicDefines.h"
#include <string>
#include <cmath>

// TODO
// Improve movement algo

EatingPerformer::EatingPerformer(World * world) :
    world(world)
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
        return;
    }

    std::vector<Object*> participants = action.getParticipants();

    // check if there are more than one participants
    if (participants.size() > 1)
    {
        action.markAsFailed();
        return;
    }

    Object * food = *participants.begin();

    // check resource type
    if (food -> getType() == RESOURCE) 
    {
        action.markAsFailed();
        return;
    }

    // get food value
    uint food_value = 0;
    action.markAsPending();
    switch(dynamic_cast<Resource*>(food) -> getSubtype())
    {
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
        dynamic_cast<Resource*>(food) -> decreaseAmount(1);
        dynamic_cast<Creature*>(actor) -> feed(food_value);
        action.markAsSucceeded();
        return;
    }


    action.markAsFailed();
}