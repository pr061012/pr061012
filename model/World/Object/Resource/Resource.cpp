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
    Object(RESOURCE, true, false),
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
            this -> makePickable();
            this -> makeNonSolid();
            this -> difficulty      = RES_DEFAULT_DIFFICULTY;
            // FIXME: Consts for wood.
            this -> amount          = res_amount != 0 ? res_amount : Random::int_range(RES_WOOD_AMOUNT_MIN, RES_WOOD_AMOUNT_MAX);
            this -> max_amount      = this -> amount;
            this -> amount_per_drop = 0;
            this -> reg_amount      = 0;
        break;

        case RES_BUILDING_MAT:
            this -> mineable        = true;
            this -> restorable      = true;
            this -> makeNonPickable();
            this -> makeSolid();
            this -> difficulty      = RES_WOOD_DIFFICULTY;
            // FIXME: Consts for wood.
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

    this -> setWeight(WGHT_RESOURCE * this -> amount);
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
// HEALTH MANIPULATION.
//******************************************************************************

void Resource::increaseMaxAmount(uint delta)
{
    this -> max_amount += delta;
}

uint Resource::damage(uint delta)
{
    uint d = delta;

    if (this -> amount < d)
    {
        d = this -> amount;
    }

    this -> amount -= d;
    this -> setWeight(WGHT_RESOURCE * this -> amount);

    return d;
}

uint Resource::heal(uint delta)
{
    uint d = delta;

    if (this -> amount + d > this -> max_amount)
    {
        d = this -> max_amount - this -> amount;
    }

    this -> amount += d;
    this -> setWeight(WGHT_RESOURCE * this -> amount);

    return d;
}

uint Resource::getHealthPoints() const
{
    return this -> amount;
}

uint Resource::getMaxHealthPoints() const
{
    return this -> max_amount;
}

//******************************************************************************
// OBJECT'S LIFE.
//******************************************************************************

std::vector<Action>* Resource::getActions()
{
    // TODO: Maybe it's better to use REGENERATE_OBJ action?
    if(this -> steps_to_reg-- == 0)
    {
        this -> heal(this -> reg_amount);
        this -> steps_to_reg = RES_REGENERATION_RATE;
    }

    this -> actions.clear();
    return &(this -> actions);
}

void Resource::receiveMessage(Message message)
{
}

std::string Resource::printObjectInfo(bool full) const
{
    std::stringstream ss;

    ss << Object::printObjectInfo(full) <<
          insertSpaces("Type");
    switch (subtype)
    {
        case RES_FOOD:         ss << "food";              break;
        case RES_BUILDING_MAT: ss << "building material"; break;
        default:               ss << "unknown";           break;
    }
    ss << "\n";

    ss << insertSpaces("Progress")      << progress << "/" << difficulty << std::endl <<
          insertSpaces("Drop amount")   << amount_per_drop << std::endl <<
          insertSpaces("Reg amount")    << reg_amount << std::endl <<
          insertSpaces("Steps to reg")  << steps_to_reg << std::endl <<
          insertSpaces("Is mineable")   << (mineable ? "yes" : "no") << std::endl <<
          insertSpaces("Is restorable") << (restorable ? "yes" : "no") << std::endl;

    return ss.str();
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

void Resource::setProgress(uint progress)
{
    this -> progress = progress;
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

void Resource::makeNonMineable()
{
    this -> mineable = false;
}

bool Resource::isRestorable() const
{
    return this -> restorable;
}

void Resource::makeRestorable()
{
    this -> restorable = true;
}

void Resource::makeNonRestorable()
{
    this -> restorable = false;
}
