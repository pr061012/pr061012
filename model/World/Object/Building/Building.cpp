/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <sstream>

#include "Building.h"
#include "../../../../common/Math/Random.h"
#include "../../../../common/BasicDefines.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Building::Building(uint max_space, uint max_health) :
    Object(BUILDING, false),
    contents(new ObjectHeap),
    health(1),
    max_health(max_health),
    free_space(max_space),
    max_space(max_space),
    completeness(false)
{
    this -> setDangerLevel(DNGR_BUILDING);
    this -> setShapeType(SHP_BUILDING);
    this -> setShapeSize(Random::double_range(SZ_BUILDING_SIDE_MIN, SZ_BUILDING_SIDE_MAX));
    this -> setWeight(WGHT_BUILDING);
}

Building::~Building()
{
    delete contents;
}

//******************************************************************************
// INHERETED THINGS.
//******************************************************************************

std::vector<Action>* Building::getActions()
{
    this -> actions.clear();
    return &(this -> actions);
}

void Building::receiveMessage(Message message)
{
}

std::string Building::printObjectInfo(bool full) const
{
    std::string output = Object::printObjectInfo(full);

    std::stringstream ss;

    ss << "Is complete\t\t" << (completeness ? "yes" : "no") << std::endl <<
          "Free space\t\t"  << free_space << "/" << max_space << std::endl <<
          "Contents"        << std::endl << contents -> printIDs();

    return output + ss.str();
}

std::string Building::getTypeName() const
{
    return "building";
}

//******************************************************************************
// HEALTH MANIPULATION.
//******************************************************************************

uint Building::damage(uint delta)
{
    uint d = delta;

    if (this -> health < d)
    {
        d = this -> health;
    }

    this -> health -= d;
    return d;
}

uint Building::heal(uint delta)
{
    uint d = delta;

    if (this -> health + d > this -> max_health)
    {
        d = this -> max_health - this -> health;
    }

    this -> health += d;

    if (this -> health == this -> max_health)
    {
        this -> completeness = true;
        this -> makeSolid();
    }

    return d;
}

uint Building::getHealthPoints() const
{
    return this -> health;
}

uint Building::getMaxHealthPoints() const
{
    return this -> max_health;
}

//******************************************************************************
// CONTENTS MANIPULATION.
//******************************************************************************

bool Building::putInside(Object * object)
{
    return this -> contents -> push(object);
}

bool Building::takeOut(Object * object)
{
    return this -> contents -> remove(object);
}

//******************************************************************************
// CONTENTS AND SPACE ACCESSORS.
//******************************************************************************

ObjectHeap * Building::getContents()
{
    return this -> contents;
}

uint Building::getFreeSpace()
{
    return this -> free_space;
}

uint Building::getMaxSpace()
{
    return this -> max_space;
}

bool Building::getCompleteness()
{
    return this -> completeness;
}
