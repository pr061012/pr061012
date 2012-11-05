/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>

#include "NonHumanoid.h"
#include "../../../../BasicDefines.h"
#include "../../../../BasicTypes.h"
#include "../../../../BasicFuncs.h"

using namespace arma; //?

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

NonHumanoid::NonHumanoid(const DecisionMaker & dmaker) :
    Creature(NON_HUMANOID, dmaker)
{
    // Randomly initialize some values.
    int age    = randFromRange(NHUM_AGE_MIN,    NHUM_AGE_MAX);

    // Initialize some inhereted things.
    setMaxAge(age);
    setAge(0);

    // Initialize of matrix of attr
    attrs(ATTR_HEALTH,0)         = 100 * hunger / max_hunger;
    attrs(ATTR_SLEEPINESS,0)     = 100 * sleepiness / max_sleepiness;
    attrs(ATTR_NEED_IN_HOUSE,0)  = 0;
    attrs(ATTR_NEED_IN_POINTS,0) = 0;
    attrs(ATTR_LAZINESS,0)       = 100; // our animal is very lazy, so it always wants to relax
    attrs(ATTR_HEALTH,0)         = (100 - health) / max_health;
    attrs(ATTR_COMMUNICATION,0)  = 0;
    attrs(ATTR_SAFETY,0)         = safety;
    attrs(ATTR_NEED_IN_DESC,0)   = need_in_descendants;

    // Initialize of steps
    age_steps       = CREAT_AGE_STEPS;
    common_steps    = CREAT_STEPS;
    safety_steps    = CREAT_SAFETY_STEPS;
    desc_steps      = CREAT_DESC_STEPS;
    decr_sleep_step = 0;

    // Initialize of current decision
    current_decision = NONE;
}

NonHumanoid::~NonHumanoid()
{

}

std::vector <Action>* NonHumanoid::getActions()
{
    this -> age_steps--;
    this -> common_steps--;
    this -> safety_steps--;
    this -> desc_steps--;
    if (!this -> decr_sleep_step)
        this -> decr_sleep_step--;

    if(age_steps == 0)
        updateAge();
    if(desc_steps == 0)
        updateNeedInDesc();
    if(common_steps == 0)
        updateCommonAttrs();
    if(safety_steps == 0)
        updateSafety();

    this -> actions.clear();

    if (current_decision == NONE || safety > CREAT_SAF_CRIT_CONST)
        current_decision = brains.makeDecision(attrs);

    if (current_decision == SLEEP)
    {
        if (decr_sleep_step == 0)
        {
            if (sleepiness > 0)
            {
                sleepiness--;
            }
            else
                sleepiness = 0;

            decr_sleep_step = NHUM_DECR_SLEEP_STEPS;
        }
    }


    return &actions;

}

void NonHumanoid::updateAge()
{
    this -> age--; // age 0 - NHum is died
    this -> age_steps = CREAT_AGE_STEPS;
}

void NonHumanoid::updateNeedInDesc()
{
    this -> need_in_descendants += NHUM_DELTA_NEED_IN_DESC;
    this -> attrs(ATTR_NEED_IN_DESC,0) = need_in_descendants;
    this -> desc_steps = CREAT_DESC_STEPS;
}

void NonHumanoid::updateCommonAttrs()
{
    if (current_decision != EAT)
        this -> hunger     += CREAT_DELTA_HUNGER;
    if (current_decision != SLEEP)
        this -> sleepiness += CREAT_DELTA_SLEEP;

    this -> attrs(ATTR_HUNGER,0)     = 100 * hunger / max_hunger;
    this -> attrs(ATTR_SLEEPINESS,0) = 100 * sleepiness / max_sleepiness; // what about health?

    this -> common_steps = CREAT_STEPS;
}

void NonHumanoid::updateSafety()
{
    ;
}

