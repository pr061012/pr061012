/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "../../../../BasicTypes.h"
#include "../Defines.h"
#include "NonHumanoid.h"

//******************************************************************************
// STATIC FUNCTIONS.
//******************************************************************************

static inline int randFromRange(int low_boundary, int top_boundary)
{
    return rand() % (top_boundary - low_boundary) + low_boundary + 1;
}

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

NonHumanoid::NonHumanoid(const DecisionMaker & dmaker) :
    Creature(dmaker)
{
    this -> type = NONHUMANOID;

    // Initialize some inhereted things.
    int health = randFromRange(NHUM_HEALTH_MIN, NHUM_HEALTH_MAX);
    setMaxHealth(health);
    setHealth(health);

    // Randomly initialize some values.
    this -> max_age = randFromRange(NHUM_AGE_MIN, NHUM_AGE_MAX);

    // Initialize other values.
    this -> age = this -> max_age;
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
