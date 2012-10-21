/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "../../../../BasicTypes.h"
#include "../Defines.h"
#include "Humanoid.h"

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

Humanoid::Humanoid(const DecisionMaker & dmaker) :
    Creature(dmaker)
{
    this -> type = HUMANOID;

    // Randomly initialize some values.
    this -> max_health = randFromRange(HUM_HEALTH_MIN, HUM_HEALTH_MAX);
    this -> max_age    = randFromRange(HUM_AGE_MIN,    HUM_AGE_MAX);

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
    // Preparing main attributes.
    unsigned int relative_satiety     = 100 * satiety     / max_satiety;
    unsigned int relative_sleepiness  = 100 * sleepiness  / max_sleepiness;
    unsigned int relative_sociability = 100 * sociability / max_sociability;

    // TODO Preparing Vector of attributes.
}
