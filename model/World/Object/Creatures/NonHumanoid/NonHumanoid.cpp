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
    Object(CREATURE),
    Creature(HUMANOID, dmaker)
{
    // Randomly initialize some values.
    int age    = randFromRange(NHUM_AGE_MIN,    NHUM_AGE_MAX);

    // Initialize some inhereted things.
    setMaxAge(age);
    setAge(0);
}

NonHumanoid::~NonHumanoid()
{

}
