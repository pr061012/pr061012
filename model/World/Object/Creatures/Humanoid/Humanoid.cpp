/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>
#include <armadillo>

#include "Humanoid.h"
#include "../Defines.h"
#include "../../../../BasicTypes.h"
#include "../../../../BasicFunc.h"


//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

int Humanoid::CURRENT_ID = 0;

Humanoid::Humanoid(const DecisionMaker & dmaker) :
    Object(CREATURE),
    Creature(HUMANOID, dmaker),
    id(CURRENT_ID++)
{
    int age    = randFromRange(HUM_AGE_MIN,    HUM_AGE_MAX);

    // Initialize some inhereted things.
    setMaxAge(age);
    setMaxAge(0);

    // TODO: Randomly initialize humanoid's name.
    name = "Name";

    // Randomly initialize some values.
    max_sociability = randFromRange(HUM_SOCIABILITY_MIN, HUM_SOCIABILITY_MAX);
    laziness        = randFromRange(HUM_LAZINESS_MIN,    HUM_LAZINESS_MAX);

    // Initialize other values.
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
