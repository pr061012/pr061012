/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <sstream>

#include "Building.h"
#include "../../../common/Math/Random.h"
#include "../../../common/BasicDefines.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Building::Building(uint max_space, uint max_health) :
    Object(BUILDING, true, false),
    contents(new ObjectHeap),
    health(1),
    max_health(max_health),
    free_space(max_space),
    max_space(max_space),
    completeness(false)
{
    // Setting shape parameters.
    this -> setShapeType(SHP_BUILDING);
    this -> setShapeSize(Random::double_range(SZ_BUILDING_SIDE_MIN, SZ_BUILDING_SIDE_MAX));

    // Setting danger level and weight.
    this -> setDangerLevel(DNGR_BUILDING);
    this -> setWeight(WGHT_BUILDING);
}

Building::~Building()
{
    delete contents;
}

//******************************************************************************
// INHERETED THINGS.
//******************************************************************************

std::string Building::printObjectInfo(bool full) const
{
    std::stringstream ss;

    ss << Object::printObjectInfo(full) <<
          insertSpaces("Is complete") << (completeness ? "yes" : "no") <<
                                         std::endl <<
          insertSpaces("Free space")  << free_space << "/" << max_space <<
                                         std::endl;

    if (full)
    {
        ss << "Contents" << std::endl << contents -> printIDs() << std::endl;
    }

    return ss.str();
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

    if (this -> health <= BLD_COMPLETENESS_COEF * this -> max_health)
    {
        this -> completeness = false;
    }

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

bool Building::putInside(Object* object)
{
    if (!this -> completeness)
    {
        return false;
    }

    uint w = object -> getWeight();

    if (this -> free_space >= w && this -> contents -> push(object))
    {
        this -> free_space -= w;
        return true;
    }

    return false;
}

bool Building::takeOut(Object* object)
{
    if (this -> contents -> remove(object))
    {
        this -> free_space += object -> getWeight();
        return true;
    }

    return false;
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
