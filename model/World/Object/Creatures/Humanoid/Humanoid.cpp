/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>
#include <armadillo>

#include "Humanoid.h"
#include "../../../../../common/BasicDefines.h"
#include "../../../../../common/Random/Random.h"


//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

int Humanoid::CURRENT_ID = 0;

Humanoid::Humanoid(const DecisionMaker & dmaker) :
    Creature(HUMANOID, dmaker),
    id(CURRENT_ID++)
{
    int age = Random::int_range(HUM_AGE_MIN, HUM_AGE_MAX);

    // Initialize some inhereted things.
    this -> setMaxAge(age);
    this -> setMaxAge(0);
    this -> setShapeSize(SZ_HUMANOID_DIAM);
    this -> setShapeType(SHP_HUMANOID);

    // TODO: Randomly initialize humanoid's name.
    name = "Name";

    // Randomly initialize some values.
    max_sociability = Random::int_range(HUM_SOCIABILITY_MIN, HUM_SOCIABILITY_MAX);
    laziness        = Random::int_range(HUM_LAZINESS_MIN,    HUM_LAZINESS_MAX);

    // Initialize other values.
    sociability    = 100 - max_sociability;
    need_in_points = 100;
    need_in_house  = 100;

    //Initialize of matrix of attr
    attrs(ATTR_HUNGER,0)         = 100 * hunger / max_hunger;
    attrs(ATTR_SLEEPINESS,0)     = 100 * sleepiness / max_sleepiness;
    attrs(ATTR_NEED_IN_HOUSE,0)  = need_in_house;
    attrs(ATTR_NEED_IN_POINTS,0) = need_in_points;
    attrs(ATTR_LAZINESS,0)       = laziness;
    attrs(ATTR_HEALTH,0)         = 100 * (100 - health) / max_health;
    attrs(ATTR_COMMUNICATION,0)  = 100 * sociability / max_sociability;
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

    this -> actions.clear();

    if (!brains.isDecisionActual(attrs, current_decision))
    {
        current_decision = NONE;
        angle = -1;
        aim = 0;
    }
    if (current_decision == NONE)
    {
        current_decision = brains.makeDecision(attrs);
        angle = -1;
        aim = 0;
        detailed_act = chooseAction(current_decision);
    }

    if (detailed_act == REALAX_AT_HOME)
    {

    }

    if (detailed_act == HUNT)
    {

    }

    if (detailed_act == FIND_FOOD)
    {

    }

    if (detailed_act == SLEEP_AT_HOME)
    {

    }

    if (detailed_act == SLEEP_ON_THE_GROUND)
    {

    }

    if (detailed_act == MINE_RESOURSES)
    {

    }

    if (detailed_act == BUILD_HOUSE)
    {

    }

    if (detailed_act == TAKE_FOOD_FROM_INVENTORY)
    {

    }

    if (detailed_act == FIGHT)
    {

    }

    if (detailed_act == RUN_FROM_DANGER)
    {

    }
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
    this -> hunger      += CREAT_DELTA_HUNGER;
    this -> sleepiness  += CREAT_DELTA_SLEEP;
    this -> sociability += HUM_DELTA_SOC;

    this -> attrs(ATTR_HUNGER,0)        = 100 * hunger / max_hunger;
    this -> attrs(ATTR_SLEEPINESS,0)    = 100 * sleepiness / max_sleepiness; // what about health?
    this -> attrs(ATTR_COMMUNICATION,0) = 100 * sociability / max_sociability;

    this -> common_steps = CREAT_STEPS;
    // TODO: func to calculate health, need in house and need in points
}

void Humanoid::updateSafety()
{
    ;
}

DetailedHumAction Humanoid::chooseAction(CreatureAction action)
{
    DetailedHumAction result_act = REALAX_AT_HOME;

    // Draft of father processing
    switch(action)
    {
    case EAT: result_act = chooseWayToEat(); break;
    case SLEEP: result_act = chooseWayToSleep(); break;
    case COMMUNICATE: ; break;
    case RELAX: result_act = chooseWayToRelax(); break;
    case WORK: ; break;
    case REALIZE_DREAM: ; break;
    case ESCAPE: result_act = this -> chooseWayToEscape(); break;
    case BUILD: result_act = chooseWayToBuild(); break;
    case CONTINUE_GENDER: ; break;
    default: ;
    }

    return result_act;
}

DetailedHumAction Humanoid::chooseWayToRelax()
{
    return REALAX_AT_HOME;
}

DetailedHumAction Humanoid:: chooseWayToBuild()
{

}

DetailedHumAction Humanoid:: chooseWayToEat()
{

}

DetailedHumAction Humanoid:: chooseWayToSleep()
{

}

DetailedHumAction Humanoid:: chooseWayToEscape()
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
