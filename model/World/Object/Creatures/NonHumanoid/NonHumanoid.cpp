/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "NonHumanoid.h"

NonHumanoid::NonHumanoid(const DecisionMaker & dmaker) :
    Creature(dmaker)
{
    this -> type = NONHUMANOID;
}

NonHumanoid::~NonHumanoid()
{

}

void NonHumanoid::step()
{

}
