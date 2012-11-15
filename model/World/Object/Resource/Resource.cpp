/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Resource.h"

#include "../../../BasicDefines.h"
#include "../../../BasicFuncs.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Resource::Resource(ResourceType type, uint res_amount) :
    Object(RESOURCE),
    subtype(type),
    progress(0),
    steps_to_reg(0)
{
    this -> setShapeType(SHP_RESOURCE);
    this -> setShapeSize(randFromRange(SZ_RESOURCE_DIAM_MIN, SZ_RESOURCE_DIAM_MAX));

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
// CHANGING PROGRESS.
//******************************************************************************

void Resource::incrementProgress()
{
    this -> progress++;
}

//******************************************************************************
// CHANGING AMOUNT.
//******************************************************************************

void Resource::decreaseAmount(uint delta)
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

void Resource::increaseAmount(uint delta)
{
    // TODO: We don't have top boundary yet. Do we need it?
    this -> amount += delta;
}

uint Resource::getAmount() const
{
    return this -> amount;
}

void Resource::damage(uint delta)
{
    this -> decreaseAmount(delta);
}

void Resource::heal(uint delta)
{
    this -> increaseAmount(delta);
}

//******************************************************************************
// OBJECT'S LIFE.
//******************************************************************************

std::vector <Action> * Resource::getActions()
{
    if(this -> steps_to_reg-- == 0)
    {
        this -> increaseAmount(this -> reg_amount);
        this -> steps_to_reg = RES_REGENERATION_RATE;
    }

    this -> actions.clear();

    if(this -> progress >= this -> difficulty)
    {
        this -> progress = 0;

        uint drop_amount;
        if(this -> amount_per_drop > this -> amount)
        {
            drop_amount = this -> amount;
        }
        else
        {
            drop_amount = this -> amount_per_drop;
        }

        // TODO: Add x and y.
        Action act(CREATE_OBJ, this);
        act.addParam("obj_type", RESOURCE);
        // FIXME: Won't work. Subtype is IRON_ORE, we need drop IRON. How to do
        // that?
        act.addParam("res_type", this -> subtype);
        act.addParam("res_amount", drop_amount);
        this -> actions.push_back(act);
    }

    return &(this -> actions);
}

uint Resource::getHealthPoints() const
{
    return this -> amount;
}

uint Resource::getMaxHealthPoints() const
{
    return this -> amount;
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

uint Resource::getProgress() const
{
    return this -> progress;
}

uint Resource::getDifficulty() const
{
    return this -> difficulty;
}

bool Resource::isMineable() const
{
    return this -> mineable;
}
