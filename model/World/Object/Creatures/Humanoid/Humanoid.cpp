/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>
#include <armadillo>

#include "Humanoid.h"
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

Humanoid::Humanoid(const DecisionMaker & dmaker) :
    Object(CREATURE),
    Creature(HUMANOID, dmaker),
    // FIXME: ld fails here
    id(CURRENT_ID++)
{
    int health = randFromRange(HUM_HEALTH_MIN, HUM_HEALTH_MAX);
    int age    = randFromRange(HUM_AGE_MIN,    HUM_AGE_MAX);

    // Initialize some inhereted things.
    setMaxHealth(health);
    setHealth(health);
    setMaxAge(age);
    setMaxAge(0);

    // TODO: Randomly initialize humanoid's name.
    name = "Name";

    // Randomly initialize some values.
    max_hunger      = randFromRange(HUM_HUNGER_MIN,     HUM_HUNGER_MAX);
    max_sleepiness  = randFromRange(HUM_SLEEPINESS_MIN,  HUM_SLEEPINESS_MAX);
    max_sociability = randFromRange(HUM_SOCIABILITY_MIN, HUM_SOCIABILITY_MAX);
    laziness        = randFromRange(HUM_LAZINESS_MIN,    HUM_LAZINESS_MAX);

    // Initialize other values.
    hunger      = max_hunger;
    sleepiness  = max_sleepiness;
    sociability = max_sociability;
}

Humanoid::~Humanoid()
{

}

//******************************************************************************
// HUMANOID'S LOGICS.
//******************************************************************************

//~ void Humanoid::step()
//~ {
    //~ // Preparing main attributes.
    //~ unsigned int relative_hunger      = 100 * hunger      / max_hunger;
    //~ unsigned int relative_sleepiness  = 100 * sleepiness  / max_sleepiness;
    //~ unsigned int relative_sociability = 100 * sociability / max_sociability;
//~ 
    //~ // Preparing vector of attributes.
    //~ arma::vec attrs(9);
    //~ attrs << relative_hunger << relative_sleepiness << need_in_house <<
             //~ need_in_res << laziness << getHealth() << relative_sociability <<
             //~ safety;
//~ 
    //~ // TODO Spawning desicion maker.
//~ }
