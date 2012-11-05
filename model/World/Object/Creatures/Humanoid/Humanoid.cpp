/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>
#include <armadillo>

#include "Humanoid.h"
#include "../../../../BasicDefines.h"
#include "../../../../BasicTypes.h"
#include "../../../../BasicFuncs.h"


//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

int Humanoid::CURRENT_ID = 0;

Humanoid::Humanoid(const DecisionMaker & dmaker) :
    Creature(HUMANOID, dmaker),
    id(CURRENT_ID++)
{
    int age = randFromRange(HUM_AGE_MIN, HUM_AGE_MAX);

    // Initialize some inhereted things.
    setMaxAge(age);
    setMaxAge(0);

    // TODO: Randomly initialize humanoid's name.
    name = "Name";

    // Randomly initialize some values.
    max_sociability = randFromRange(HUM_SOCIABILITY_MIN, HUM_SOCIABILITY_MAX);
    laziness        = randFromRange(HUM_LAZINESS_MIN,    HUM_LAZINESS_MAX);

    // Initialize other values.
    sociability    = max_sociability;
    need_in_points = 100;
    need_in_house  = 100;

    //Initialize of matrix of attr
    attrs(ATTR_HEALTH,0)         = (100 - hunger) / max_hunger * 100;
    attrs(ATTR_SLEEPINESS,0)     = (100 - sleepiness) / max_sleepiness * 100;
    attrs(ATTR_NEED_IN_HOUSE,0)  = need_in_house;
    attrs(ATTR_NEED_IN_POINTS,0) = need_in_points;
    attrs(ATTR_LAZINESS,0)       = laziness;
    attrs(ATTR_HEALTH,0)         = (100 - health) / max_health * 100;
    attrs(ATTR_COMMUNICATION,0)  = (100 - sociability) / max_sociability * 100;
    attrs(ATTR_SAFETY,0)         = safety;
    attrs(ATTR_NEED_IN_DESC,0)   = need_in_descendants;
}

Humanoid::~Humanoid()
{

}

std::vector <Action>* Humanoid::getActions()
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

void Humanoid::updateAge()
{
    this -> age--; // age 0 - Hum is died
    this -> age_steps = CREAT_AGE_STEPS;
}

void Humanoid::updateNeedInDesc()
{
    this -> need_in_descendants += HUM_DELTA_NEED_IN_DESC; // need 0 NHum dont need in descendant
    this -> attrs(ATTR_NEED_IN_DESC,0) = need_in_descendants; // we dont need in transformation this attr
    this -> desc_steps = CREAT_DESC_STEPS;
}

void Humanoid::updateCommonAttrs()
{
    this -> hunger      -= CREAT_DELTA_HUNGER; // so if hunger = 0 NHum is died we need to decrease this attr
    this -> sleepiness  -= CREAT_DELTA_SLEEP;
    this -> sociability -= HUM_DELTA_SOC;

    this -> attrs(ATTR_HUNGER,0)        = (100 - hunger) / max_hunger * 100; // transformation to matrix attr
    this -> attrs(ATTR_SLEEPINESS,0)    = (100 - sleepiness) / max_sleepiness * 100; // what about health?
    this -> attrs(ATTR_COMMUNICATION,0) = (100 - sociability) / max_sociability * 100;

    this -> common_steps = CREAT_STEPS;
    // TODO: func to calculate health, need in house and need in points
}

void Humanoid::updateSafety()
{
    ;
}

CreatureAction Humanoid::chooseAction()
{
    CreatureAction action = NONE;
    // action = brains -> makeDecision(attrs);
    // error!!

    // Draft of father processing
    switch(action)
    {
    case EAT: ; break;
    case SLEEP: ; break;
    case COMMUNICATE: ; break;
    case RELAX: ; break;
    case WORK: ; break;
    case REALIZE_DREAM: ; break;
    case ESCAPE: ; break;
    case BUILD: ; break;
    case CONTINUE_GENDER: ; break;
    default: ;
    }

    return action;
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
