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

Resource::Resource(ResourceType type, unsigned int res_amount) :
    Object(RESOURCE),
    subtype(type),
    progress(0),
    steps_to_reg(0)
{
    // FIXME: Foolish code.
    switch(this -> subtype)
    {
        case WOOD:
            this -> mineable        = true;
            this -> difficulty      = RES_WOOD_DIFFICULTY;
            this -> amount          = res_amount != 0 ? res_amount : randFromRange(RES_WOOD_AMOUNT_MIN, RES_WOOD_AMOUNT_MAX);
            this -> amount_per_drop = randFromRange(RES_WOOD_DROP_MIN, RES_WOOD_DROP_MAX);
            this -> reg_amount      = RES_WOOD_REG_AMOUNT;
        break;

        case BRONZE_ORE:
            this -> mineable        = true;
            this -> difficulty      = RES_BRONZE_ORE_DIFFICULTY;
            this -> amount          = res_amount != 0 ? res_amount : randFromRange(RES_BRONZE_ORE_AMOUNT_MIN, RES_BRONZE_ORE_AMOUNT_MAX);
            this -> amount_per_drop = randFromRange(RES_BRONZE_ORE_DROP_MIN, RES_BRONZE_ORE_DROP_MAX);
            this -> reg_amount      = RES_BRONZE_ORE_REG_AMOUNT;
        break;

        case IRON_ORE:
            this -> mineable        = true;
            this -> difficulty      = RES_IRON_ORE_DIFFICULTY;
            this -> amount          = res_amount != 0 ? res_amount : randFromRange(RES_IRON_ORE_AMOUNT_MIN, RES_IRON_ORE_AMOUNT_MAX);
            this -> amount_per_drop = randFromRange(RES_IRON_ORE_DROP_MIN, RES_IRON_ORE_DROP_MAX);
            this -> reg_amount      = RES_IRON_ORE_REG_AMOUNT;
        break;

        case SILVER_ORE:
            this -> mineable        = true;
            this -> difficulty      = RES_SILVER_ORE_DIFFICULTY;
            this -> amount          = res_amount != 0 ? res_amount : randFromRange(RES_SILVER_ORE_AMOUNT_MIN, RES_SILVER_ORE_AMOUNT_MAX);
            this -> amount_per_drop = randFromRange(RES_SILVER_ORE_DROP_MIN, RES_SILVER_ORE_DROP_MAX);
            this -> reg_amount      = RES_SILVER_ORE_REG_AMOUNT;
        break;

        case GOLD_ORE:
            this -> mineable        = true;
            this -> difficulty      = RES_GOLD_ORE_DIFFICULTY;
            this -> amount          = res_amount != 0 ? res_amount : randFromRange(RES_GOLD_ORE_AMOUNT_MIN, RES_GOLD_ORE_AMOUNT_MAX);
            this -> amount_per_drop = randFromRange(RES_GOLD_ORE_DROP_MIN, RES_GOLD_ORE_DROP_MAX);
            this -> reg_amount      = RES_GOLD_ORE_REG_AMOUNT;
        break;

        default:
            this -> mineable        = false;
            this -> difficulty      = 0;
            this -> amount          = res_amount;
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
    if(this -> steps_to_reg-- == 0)
    {
        // TODO: We don't have top boundary yet. Do we need it?
        this -> amount += this -> reg_amount;
        this -> steps_to_reg = RES_REGENERATION_RATE;
    }

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
