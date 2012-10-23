/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>

#include "NonHumanoid.h"
#include "../Defines.h"
#include "../../../../BasicTypes.h"

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
    // Randomly initialize some values.
    int health = randFromRange(NHUM_HEALTH_MIN, NHUM_HEALTH_MAX);
    int age    = randFromRange(NHUM_AGE_MIN,    NHUM_AGE_MAX);

    // Initialize some inhereted things.
    setType(NONHUMANOID);
    setMaxHealth(health);
    setHealth(health);
    setMaxAge(age);
    setAge(0);
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
