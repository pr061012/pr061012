/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include <sstream>

#include "Resource.h"

#include "../../../../common/BasicDefines.h"
#include "../../../../common/Math/Random.h"

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
    this -> setShapeSize(Random::double_range(SZ_RESOURCE_DIAM_MIN, SZ_RESOURCE_DIAM_MAX));
    this -> setDangerLevel(DNGR_RESOURCE);

    // FIXME: Foolish code.
    switch(this -> subtype)
    {
        case RES_FOOD:
            this -> mineable        = false;
            this -> restorable      = false;
            this -> makeNonSolid();
            this -> difficulty      = RES_DEFAULT_DIFFICULTY;
            this -> amount          = res_amount;
            this -> max_amount      = res_amount;
            this -> amount_per_drop = 0;
            this -> reg_amount      = 0;
        break;

        case RES_BUILDING_MAT:
            this -> mineable        = true;
            this -> restorable      = true;
            this -> makeSolid();
            this -> difficulty      = RES_WOOD_DIFFICULTY;
            this -> amount          = res_amount != 0 ? res_amount : Random::int_range(RES_WOOD_AMOUNT_MIN, RES_WOOD_AMOUNT_MAX);
            this -> max_amount      = 1.5 * this -> amount;
            this -> amount_per_drop = Random::int_range(RES_WOOD_DROP_MIN, RES_WOOD_DROP_MAX);
            this -> reg_amount      = RES_WOOD_REG_AMOUNT;
        break;

        /*
        case WOOD:
            this -> mineable        = true;
            this -> difficulty      = RES_WOOD_DIFFICULTY;
            this -> amount          = res_amount != 0 ? res_amount : Random::int_range(RES_WOOD_AMOUNT_MIN, RES_WOOD_AMOUNT_MAX);
            this -> amount_per_drop = Random::int_range(RES_WOOD_DROP_MIN, RES_WOOD_DROP_MAX);
            this -> reg_amount      = RES_WOOD_REG_AMOUNT;
        break;

        case BRONZE_ORE:
            this -> mineable        = true;
            this -> difficulty      = RES_BRONZE_ORE_DIFFICULTY;
            this -> amount          = res_amount != 0 ? res_amount : Random::int_range(RES_BRONZE_ORE_AMOUNT_MIN, RES_BRONZE_ORE_AMOUNT_MAX);
            this -> amount_per_drop = Random::int_range(RES_BRONZE_ORE_DROP_MIN, RES_BRONZE_ORE_DROP_MAX);
            this -> reg_amount      = RES_BRONZE_ORE_REG_AMOUNT;
        break;

        case IRON_ORE:
            this -> mineable        = true;
            this -> difficulty      = RES_IRON_ORE_DIFFICULTY;
            this -> amount          = res_amount != 0 ? res_amount : Random::int_range(RES_IRON_ORE_AMOUNT_MIN, RES_IRON_ORE_AMOUNT_MAX);
            this -> amount_per_drop = Random::int_range(RES_IRON_ORE_DROP_MIN, RES_IRON_ORE_DROP_MAX);
            this -> reg_amount      = RES_IRON_ORE_REG_AMOUNT;
        break;

        case SILVER_ORE:
            this -> mineable        = true;
            this -> difficulty      = RES_SILVER_ORE_DIFFICULTY;
            this -> amount          = res_amount != 0 ? res_amount : Random::int_range(RES_SILVER_ORE_AMOUNT_MIN, RES_SILVER_ORE_AMOUNT_MAX);
            this -> amount_per_drop = Random::int_range(RES_SILVER_ORE_DROP_MIN, RES_SILVER_ORE_DROP_MAX);
            this -> reg_amount      = RES_SILVER_ORE_REG_AMOUNT;
        break;

        case GOLD_ORE:
            this -> mineable        = true;
            this -> difficulty      = RES_GOLD_ORE_DIFFICULTY;
            this -> amount          = res_amount != 0 ? res_amount : Random::int_range(RES_GOLD_ORE_AMOUNT_MIN, RES_GOLD_ORE_AMOUNT_MAX);
            this -> amount_per_drop = Random::int_range(RES_GOLD_ORE_DROP_MIN, RES_GOLD_ORE_DROP_MAX);
            this -> reg_amount      = RES_GOLD_ORE_REG_AMOUNT;
        break;
        */

        default:
            this -> mineable        = false;
            this -> restorable      = false;
            this -> difficulty      = RES_DEFAULT_DIFFICULTY;
            this -> amount          = res_amount;
            this -> max_amount      = res_amount;
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
    if (this -> amount >= delta)
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
    if (this -> amount + delta <= this -> max_amount)
    {
        this -> amount += delta;
    }
    else
    {
        this -> amount = this -> max_amount;
    }
}

uint Resource::getAmount() const
{
    return this -> amount;
}

bool Resource::isRestorable() const
{
    return this -> restorable;
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

        Action act(CREATE_OBJ, this);

        act.addParam<ObjectType>("obj_type", RESOURCE);
        // FIXME: Won't work. Subtype is IRON_ORE, we need drop IRON. How to do
        // that?
        act.addParam<ResourceType>("res_type", this -> subtype);
        act.addParam<uint>("res_amount", drop_amount);

        this -> actions.push_back(act);
    }

    return &(this -> actions);
}

void Resource::receiveMessage(Message message)
{
}

std::string Resource::printObjectInfo() const
{
    std::string output = Object::printObjectInfo();

    std::stringstream ss;

    ss << "Progress\t\t"      << progress << std::endl <<
          "Difficulty\t\t"    << difficulty << std::endl <<
          "Drop amount\t\t"   << amount_per_drop << std::endl <<
          "Reg amount\t\t"    << reg_amount << std::endl <<
          "Steps to reg\t\t"  << steps_to_reg << std::endl <<
          "Is mineable\t\t"   << (mineable ? "yes" : "no") << std::endl <<
          "Is restorable\t\t" << (restorable ? "yes" : "no") << std::endl;

    return output + ss.str();
}

uint Resource::getHealthPoints() const
{
    return this -> amount;
}

uint Resource::getMaxHealthPoints() const
{
    return this -> max_amount;
}

std::string Resource::getTypeName() const
{
    return "resource";
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

uint Resource::getStepsToReg() const
{
    return this -> steps_to_reg;
}

uint Resource::getRegAmount() const
{
    return this -> reg_amount;
}

uint Resource::getAmountPerDrop() const
{
    return this -> amount_per_drop;
}

bool Resource::isMineable() const
{
    return this -> mineable;
}

void Resource::makeMineable()
{
    this -> mineable = true;
}

void Resource::makePickable()
{
    this -> mineable = false;
}
