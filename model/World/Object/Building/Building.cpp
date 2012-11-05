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
    this -> setMaxHealth(max_health);
}

Building::~Building()
{
    delete contents;
}

//******************************************************************************
// ACTIONS ACCESSING.
//******************************************************************************

std::vector <Action *> Building::getActions()
{
    this -> actions.clear();
    return &(this -> actions);
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

    if(this -> getMaxHealth() == this -> getHealth())
    {
        this -> completeness = true;
    }
}

//******************************************************************************
// ACCESSORS.
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
