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
    type = HUMANOID;

    // Initialize some inhereted things.
    int health = randFromRange(HUM_HEALTH_MIN, HUM_HEALTH_MAX);
    setMaxHealth(health);
    setHealth(health);

    // Randomly initialize some values.
    max_age         = randFromRange(HUM_AGE_MIN,         HUM_AGE_MAX);
    max_satiety     = randFromRange(HUM_SATIETY_MIN,     HUM_SATIETY_MAX);
    max_sleepiness  = randFromRange(HUM_SLEEPINESS_MIN,  HUM_SLEEPINESS_MAX);
    max_sociability = randFromRange(HUM_SOCIABILITY_MIN, HUM_SOCIABILITY_MAX);
    diligence       = randFromRange(HUM_DILIGENCE_MIN,   HUM_DILIGENCE_MAX);

    // Initialize other values.
    age         = max_age;
    satiety     = max_satiety;
    sleepiness  = max_sleepiness;
    sociability = max_sociability;
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
