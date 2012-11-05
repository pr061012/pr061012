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

    //Initialize of matrix of attr
    attrs(0,0) = hunger/max_hunger;
    attrs(1,0) = sleepiness/max_sleepiness;
    attrs(2,0) = 0;
    attrs(3,0) = 0;
    attrs(4,0) = 100; // our animal is very lazy, so it always wants to relax
    attrs(5,0) = health/max_health;
    attrs(6,0) = 0;
    attrs(7,0) = safety;
    attrs(8,0) = need_in_descendants;

    //Initialize of steps
    age_steps    = CREAT_AGE_STEPS;
    common_steps = CREAT_STEPS;
    safety_steps = CREAT_SAFETY_STEPS;
    desc_steps   = CREAT_DESC_STEPS;
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

    if(age_steps == 0)
        updateAge();

    if(desc_steps == 0)
        updateNeedInDesc();

    if(common_steps == 0)
        updateCommonAttrs();

    if(safety_steps == 0)
        updateSafety();

    return &actions;

}

void NonHumanoid::updateAge()
{
    this -> age--;
    this -> age_steps = CREAT_AGE_STEPS;
}

void NonHumanoid::updateNeedInDesc()
{
    this -> need_in_descendants += 2;
    this -> attrs(8,0) = need_in_descendants;
    this -> desc_steps = CREAT_DESC_STEPS;
}

void NonHumanoid::updateCommonAttrs()
{
    this -> hunger     += 2;
    this -> sleepiness += 1;

    this -> attrs(0,0) = hunger/max_hunger;
    this -> attrs(1,0) = sleepiness/max_sleepiness;

    this -> common_steps = CREAT_STEPS;
}

void NonHumanoid::updateSafety()
{
    ;
}

