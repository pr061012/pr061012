/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Creature.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Creature::Creature(const DecisionMaker & dmaker) :
    brains(dmaker),
    inventory(new ObjectHeap)
{

}

Creature::~Creature()
{
    delete inventory;
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void Creature::setWindow(const ObjectHeap * window)
{
    this -> window = window;
}

const ObjectHeap * Creature::getWindow()
{
    return this -> window;
}

void Creature::setViewArea(Frame view_area)
{
    this -> view_area = view_area;
}

Frame Creature::getViewArea()
{
    return this -> view_area;
}

void Creature::setAge(unsigned int age)
{
    this -> age = age;
}

unsigned int Creature::getAge()
{
    return this -> age;
}

void Creature::setMaxAge(unsigned int max_age)
{
    this -> max_age = max_age;
}

unsigned int Creature::getMaxAge()
{
    return this -> max_age;
}
