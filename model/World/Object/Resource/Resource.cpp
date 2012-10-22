/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Resource.h"

//**************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//**************************************************************************

Resource::Resource()
{

}

Resource::~Resource()
{

}

int Resource::gather(Tool tool)
{

}

void Resource::step()
{

}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void Resource::setProgress(int new_var)
{
    this -> progress = new_var;
}


int Resource::getProgres()
{
    return this -> progress;
}

void Resource::setSubtype(ResourceType new_var)
{
    this -> subtype = new_var;
}

ResourceType Resource::getSubtype()
{
    return this -> subtype;
}

void Resource::setRegenerationRate(int new_var)
{
    this -> regeneration_rate = new_var;
}

int Resource::getRegenerationRate()
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

void Resource::setDifficulty(int new_var)
{
    this -> difficulty = new_var;
}

int Resource::getDifficulty()
{
    return this -> difficulty;
}

void Resource::setAmountPerGather(int new_var)
{
    this -> amount_per_gather = new_var;
}

int Resource::getAmountPerGather()
{
    return this -> amount_per_gather;
}
