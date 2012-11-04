/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Resource.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Resource::Resource(ResourceType type) :
    Object(RESOURCE),
    subtype(type)
{
    // Mineable resources.
    if
    (
        this -> subtype == BRONZE_ORE ||
        this -> subtype == IRON_ORE ||
        this -> subtype == SILVER_ORE ||
        this -> subtype == GOLD_ORE ||
        this -> subtype == WOOD
    )
    {
        this -> mineable = true;
    }
    // Pickable resources.
    else
    {
        this -> mineable = false;
    }
}

Resource::~Resource()
{

}

//******************************************************************************
// OBJECT'S LIFE.
//******************************************************************************

void Resource::decreaseAmount(unsigned int delta)
{
    if(this -> amount >= delta)
    {
        this -> amount -= delta;
    }
    else
    {
        this -> amount = 0;
    }
}

std::vector <Action> * Resource::getActions()
{
    this -> actions.clear();

    return &(this -> actions);
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

unsigned int Resource::getProgress()
{
    return this -> progress;
}

ResourceType Resource::getSubtype()
{
    return this -> subtype;
}

unsigned int Resource::getRegenerationRate()
{
    return this -> regeneration_rate;
}

bool Resource::getGathered()
{
    return this -> gathered;
}

unsigned int Resource::getDifficulty()
{
    return this -> difficulty;
}

unsigned int Resource::getAmountPerGather()
{
    return this -> amount_per_gather;
}
