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
// RESOURCE TYPE.
//******************************************************************************

ResourceType Resource::getSubtype() const
{
    return this -> subtype;
}

//******************************************************************************
// MINING.
//******************************************************************************

unsigned int Resource::getProgress() const
{
    return this -> progress;
}

unsigned int Resource::getDifficulty() const
{
    return this -> difficulty;
}

bool Resource::isMineable() const
{
    return this -> mineable;
}
