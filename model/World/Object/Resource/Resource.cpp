/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Resource.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Resource::Resource(const ResourceType type) :
    Object(RESOURCE),
    subtype(type)
{

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

std::vector <PendingAction *> Resource::getPendingActions()
{

}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void Resource::setProgress(unsigned int new_var)
{
    this -> progress = new_var;
}

unsigned int Resource::getProgress()
{
    return this -> progress;
}

ResourceType Resource::getSubtype()
{
    return this -> subtype;
}

void Resource::setRegenerationRate(unsigned int new_var)
{
    this -> regeneration_rate = new_var;
}

unsigned int Resource::getRegenerationRate()
{
    return this -> regeneration_rate;
}

void Resource::setGathered(bool new_var)
{
    this -> gathered = new_var;
}

bool Resource::getGathered()
{
    return this -> gathered;
}

void Resource::setDifficulty(unsigned int new_var)
{
    this -> difficulty = new_var;
}

unsigned int Resource::getDifficulty()
{
    return this -> difficulty;
}

void Resource::setAmountPerGather(unsigned int new_var)
{
    this -> amount_per_gather = new_var;
}

unsigned int Resource::getAmountPerGather()
{
    return this -> amount_per_gather;
}
