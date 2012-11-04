/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Resource.h"

#include "../../../BasicDefines.h"
#include "../../../BasicFunc.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Resource::Resource(ResourceType type) :
    Object(RESOURCE),
    subtype(type),
    progress(0)
{
    switch(this -> subtype)
    {
        // TODO Case for each res. type.

        default:
            this -> mineable        = false;
            this -> difficulty      = 0;
            this -> amount_per_drop = 0;
            this -> reg_amount      = 0;
        break;
    }
}

Resource::~Resource()
{

}

//******************************************************************************
// CHANGING AMOUNT.
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

unsigned int Resource::getAmount() const
{
    return this -> amount;
}

//******************************************************************************
// OBJECT'S LIFE.
//******************************************************************************

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
