/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Creature.h"

Creature::Creature(const DecisionMaker & dmaker) :
    brains(brains)
{

}

Creature::~Creature()
{
}

void Creature::setWindow(ObjectHeap * window)
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
