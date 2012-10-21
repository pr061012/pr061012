/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "../../../../BasicTypes.h"
#include "../Defines.h"
#include "Humanoid.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Humanoid::Humanoid(const DecisionMaker & dmaker) :
    Creature(dmaker)
{
    this -> type = HUMANOID;

    // Randomly initialize some values.
    this -> max_health = rand() % (HUM_HEALTH_MAX - HUM_HEALTH_MIN) + HUM_HEALTH_MIN + 1;
    this -> max_age    = rand() % (HUM_MAX_AGE - HUM_MIN_AGE) + HUM_MIN_AGE + 1;

    // Initialize other values.
    this -> health = this -> max_health;
    this -> age    = this -> max_age;
}

Humanoid::~Humanoid()
{

}

//******************************************************************************
// HUMANOID'S LOGICS.
//******************************************************************************

void Humanoid::step()
{

}
