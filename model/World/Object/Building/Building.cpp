/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Building.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Building::Building(unsigned int max_space, unsigned int max_health) :
    Object(BUILDING),
    contents(new ObjectHeap),
    health(0),
    max_health(max_health),
    max_space(max_space),
    completeness(false)
{
}

Building::~Building()
{
    delete contents;
}

//******************************************************************************
// ACTIONS ACCESSING.
//******************************************************************************

std::vector <Action> * Building::getActions()
{
    this -> actions.clear();
    return &(this -> actions);
}

//******************************************************************************
// HEALTH MANIPULATION.
//******************************************************************************

void Building::decreaseHealth(unsigned int delta)
{
    if(this -> health > delta)
    {
        this -> health -= delta;
    }
    else
    {
        this -> health = 0;
    }
}

void Building::increaseHealth(unsigned int delta)
{
    if(this -> health + delta < this -> max_health)
    {
        this -> health += delta;
    }
    else
    {
        this -> health = this -> max_health;
    }
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
// REPAIRING.
//******************************************************************************

void Building::repair(unsigned int delta)
{
    this -> increaseHealth(delta);

    if(this -> health == this -> max_health)
    {
        this -> completeness = true;
    }
}

//******************************************************************************
// CONTENTS AND SPACE ACCESSORS.
//******************************************************************************

ObjectHeap * Building::getContents()
{
    return this -> contents;
}

unsigned int Building::getFreeSpace()
{
    return this -> free_space;
}

unsigned int Building::getMaxSpace()
{
    return this -> max_space;
}

bool Building::getCompleteness()
{
    return this -> completeness;
}
