/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Building.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Building::Building(unsigned int max_space) :
    Object(BUILDING),
    contents(new ObjectHeap),
    max_space(max_space),
    completeness(false)
{
}

Building::~Building()
{
    delete contents;
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

const ObjectHeap * Building::getContents()
{
    return this -> contents;
}

unsigned int Building::getFreeSpace()
{
    return this -> free_space;
}

void Building::setMaxSpace(unsigned int new_var)
{
    this -> max_space = new_var;
}

unsigned int Building::getMaxSpace()
{
    return this -> max_space;
}

bool Building::getCompleteness()
{
    return this -> completeness;
}
