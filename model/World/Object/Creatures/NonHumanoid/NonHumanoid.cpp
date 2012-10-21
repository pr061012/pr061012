/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "../../../../BasicTypes.h"
#include "../Defines.h"
#include "NonHumanoid.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

NonHumanoid::NonHumanoid(const DecisionMaker & dmaker) :
    Creature(dmaker)
{
    this -> type = NONHUMANOID;

    // Randomly initialize some values.
    this -> max_health = rand() % (NHUM_HEALTH_MAX - NHUM_HEALTH_MIN) + NHUM_HEALTH_MIN + 1;
    this -> max_age    = rand() % (NHUM_MAX_AGE - NHUM_MIN_AGE) + NHUM_MIN_AGE + 1;

    // Initialize other values.
    this -> health = this -> max_health;
    this -> age    = this -> max_age;
}

NonHumanoid::~NonHumanoid()
{

}

//******************************************************************************
// NON-HUMANOID'S LOGICS.
//******************************************************************************

void NonHumanoid::step()
{

}
