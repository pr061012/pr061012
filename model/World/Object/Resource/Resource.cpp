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
    this -> setDangerLevel(DNGR_RESOURCE);

    // Initialising environment resource.
    if (this -> subtype == WATER)
    {
        this -> mineable        = false;
        this -> restorable      = false;
        this -> makeNonPickable();
        this -> makeSolid();
        this -> difficulty      = RES_DEFAULT_DIFFICULTY;
        this -> amount_per_drop = 0;
        this -> reg_amount      = 0;
        this -> amount          = 1;
        this -> max_amount      = 1;
        this -> setShapeSize(Random::double_range(SZ_RES_WATER_DIAM_MIN, SZ_RES_WATER_DIAM_MAX));
    }
    // Initialising food resource.
    else if
    (
        this -> subtype == GRASS || this -> subtype == MEAT ||
        this -> subtype == BERRIES
    )
    {
        this -> mineable        = false;
        this -> restorable      = false;
        this -> makePickable();
        this -> makeNonSolid();
        this -> difficulty      = RES_DEFAULT_DIFFICULTY;
        this -> amount_per_drop = 0;
        this -> reg_amount      = 0;

        switch (this -> subtype)
        {
            case GRASS:
                this -> amount = res_amount != 0 ? res_amount : Random::int_range(RES_GRASS_AMOUNT_MIN, RES_GRASS_AMOUNT_MAX);
                this -> setShapeSize(Random::double_range(SZ_RES_GRASS_DIAM_MIN, SZ_RES_GRASS_DIAM_MAX));
            break;

            case BERRIES:
                this -> amount = res_amount != 0 ? res_amount : Random::int_range(RES_BERRIES_AMOUNT_MIN, RES_BERRIES_AMOUNT_MAX);
                this -> setShapeSize(Random::double_range(SZ_RES_BERRIES_DIAM_MIN, SZ_RES_BERRIES_DIAM_MAX));
            break;

            case MEAT:
                this -> amount = res_amount != 0 ? res_amount : Random::int_range(RES_MEAT_AMOUNT_MIN, RES_MEAT_AMOUNT_MAX);
                this -> setShapeSize(Random::double_range(SZ_RES_MEAT_DIAM_MIN, SZ_RES_MEAT_DIAM_MAX));
            break;

            default:
            break;
        }

        this -> max_amount = this -> amount;
    }
    // Initialising tree.
    else if (this -> subtype == TREE)
    {
        this -> mineable        = true;
        this -> restorable      = true;
        this -> makeNonPickable();
        this -> makeSolid();
        this -> difficulty      = RES_TREE_DIFFICULTY;
        this -> amount          = res_amount != 0 ? res_amount : Random::int_range(RES_TREE_AMOUNT_MIN, RES_TREE_AMOUNT_MAX);
        this -> max_amount      = 1.5 * this -> amount;
        this -> amount_per_drop = Random::int_range(RES_TREE_DROP_MIN, RES_TREE_DROP_MAX);
        this -> reg_amount      = RES_TREE_REG_AMOUNT;
        this -> setShapeSize(Random::double_range(SZ_RES_TREE_DIAM_MIN, SZ_RES_TREE_DIAM_MAX));
    }
    // Unknown resource type. Using defaults.
    else
    {
        this -> mineable        = false;
        this -> restorable      = false;
        this -> difficulty      = RES_DEFAULT_DIFFICULTY;
        this -> amount          = res_amount;
        this -> max_amount      = res_amount;
        this -> amount_per_drop = 0;
        this -> reg_amount      = 0;
        this -> setShapeSize(0);
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

void Resource::setMaxAmount(uint max_amount)
{
    this -> max_amount = max_amount;
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
    this -> actions.clear();

    if(this -> steps_to_reg-- == 0)
    {
        Action act(REGENERATE_OBJ, this);
        act.addParticipant(this);
        act.addParam<uint>("object_index", 0);
        this -> actions.push_back(act);

        this -> steps_to_reg = RES_REGENERATION_RATE;
    }

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
        case WATER:            ss << "water";             break;
        case GRASS:            ss << "grass";             break;
        case BERRIES:          ss << "berries";           break;
        case MEAT:             ss << "meat";              break;
        case TREE:             ss << "tree";              break;
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
