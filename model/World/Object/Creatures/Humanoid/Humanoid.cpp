/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Humanoid.h"

Humanoid::Humanoid(const DecisionMaker & dmaker) :
    Creature(dmaker)
{
    this -> type = HUMANOID;
}

Humanoid::~Humanoid()
{

}

void Humanoid::step()
{

}
