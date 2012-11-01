/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Building.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Building::Building() :
    Object(BUILDING),
    contents(new ObjectHeap)
{
    this -> completeness = false;
}

Building::~Building()
{

}

bool Building::putInside(Object * object)
{

}

bool Building::takeOut(Object * object)
{

}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

const ObjectHeap & Building::getContents()
{
    return this -> contents;
}

void Building::setFreeSpace(int new_var)
{
    this -> free_space = new_var;
}

int Building::getFreeSpace()
{
    return this -> free_space;
}

void Building::setMaxSpace(int new_var)
{
    this -> max_space = new_var;
}

int Building::getMaxSpace()
{
    return this -> max_space;
}

void Building::setCompleteness(bool new_var)
{
    this -> completeness = new_var;
}

bool Building::getCompleteness()
{
    return this -> completeness;
}
