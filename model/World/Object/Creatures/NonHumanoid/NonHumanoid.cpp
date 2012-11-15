/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>
#include <cmath>

#include "NonHumanoid.h"
#include "../../Resource/Resource.h"
#include "../../../../BasicDefines.h"
#include "../../../../../common/Random/Random.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

NonHumanoid::NonHumanoid(const DecisionMaker & dmaker) :
    Creature(NON_HUMANOID, dmaker)
{
    // Randomly initialize some values.
    int age = Random::int_range(NHUM_AGE_MIN, NHUM_AGE_MAX);

    // Initialize some inhereted things.
    this -> setMaxAge(age);
    this -> setAge(0);
    this -> setShapeSize(SZ_NON_HUMANOID_DIAM);
    this -> setShapeType(SHP_NON_HUMANOID);

    // Initialize of matrix of attr
    attrs(ATTR_HEALTH,0)         = 100 * hunger / max_hunger;
    attrs(ATTR_SLEEPINESS,0)     = 100 * sleepiness / max_sleepiness;
    attrs(ATTR_NEED_IN_HOUSE,0)  = 0;
    attrs(ATTR_NEED_IN_POINTS,0) = 0;
    attrs(ATTR_LAZINESS,0)       = 100; // our animal is very lazy,
                                        // so it always wants to relax
    attrs(ATTR_HEALTH,0)         = 100 * (100 - health) / max_health;
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
    // Initialize direction
    // angle =-1 means that NonHum doesn't choose any direction still
    // aim = 0 means the same
    angle = -1;
    aim = 0;

    //Initialize type
    type = COW;
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

    if (age_steps == 0)
        updateAge();
    if (desc_steps == 0)
        updateNeedInDesc();
    if (common_steps == 0)
        updateCommonAttrs();
    if (safety_steps == 0)
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
    }

    if (current_decision == SLEEP)
    {
        if (decr_sleep_step == 0)
        {
            if (sleepiness > 0)
            {
                sleepiness--;
            }
            else
            {
                current_decision = NONE;
            }

            decr_sleep_step = NHUM_DECR_SLEEP_STEPS;
        }
    }

    if (current_decision == RELAX)
    {
        if (angle == -1)
        {
            angle = Random::double_num(2 * M_PI);
        }
        Action act(GO, this);
        act.addParam<double>("angle", angle);
        act.addParam<SpeedType>("speed", SLOW_SPEED);
        this -> actions.push_back(act);
    }

    if (current_decision == EAT)
    {
        if (aim == 0);
            findGrass();

        if (aim != 0)
        {
            if (angle == -1)
                angle = setDirection();
            if (this -> getCoords().getDistance(aim -> getCoords()) == 0)
                                                   // FIXME: maybe<some_epsilon?
            {
                Action act(EAT_OBJ, this);
                act.addParticipant(aim);
            }
            else
            {
                Action act(GO, this);
                act.addParam<double>("angle", angle);
                act.addParam<SpeedType>("speed", SLOW_SPEED);
                this -> actions.push_back(act);
            }
        }
        else
        {
            // FIXME: Erm. Is using -1 as a sign of uncertainty good idea?
            if (angle == -1)
            {
                angle = Random::double_num(2 * M_PI);
            }
            Action act(GO, this);
            act.addParam<double>("angle", angle);
            act.addParam<SpeedType>("speed", SLOW_SPEED);
            this -> actions.push_back(act);
        }

        if (hunger == 0)
        {
            this -> current_action = NONE;
            angle = -1;
            aim = 0;
        }

    }

    if (current_decision == ESCAPE)
    {
        if (this -> type == COW ||
            this -> type == GOOSE ||
            this -> type == SHEEP)
        {
            if (angle == -1)
            {
                angle = Random::double_num(2 * M_PI);
            }
            Action act(GO, this);
            act.addParam<double>("angle", angle);
            act.addParam<SpeedType>("speed", FAST_SPEED);
            this -> actions.push_back(act);
        }
        else
        {

        }

    }

    if (current_decision == CONTINUE_GENDER)
    {

    }

    if (age == max_age)
    {
        health = 0;
    }

    return &actions;

}

void NonHumanoid::updateAge()
{
    this -> age++;
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
        this -> hunger   += CREAT_DELTA_HUNGER;
    if (current_decision != SLEEP)
        this -> sleepiness += CREAT_DELTA_SLEEP;

    this -> attrs(ATTR_HUNGER,0)     = 100 * hunger / max_hunger;
    this -> attrs(ATTR_SLEEPINESS,0) = 100 * sleepiness / max_sleepiness;

    this -> common_steps = CREAT_STEPS;
}

void NonHumanoid::updateSafety()
{
    ;
}

double NonHumanoid::setDirection()
{
    double delta_x;
    double delta_y;
    delta_x = aim -> getCoords().getX() - this -> getCoords().getX();
    delta_y = aim -> getCoords().getY() - this -> getCoords().getY();
    return angle = atan(delta_x / delta_y);
}

void NonHumanoid::findGrass()
{
    ObjectHeap::const_iterator iter;
    Point coords;

    double distance = SZ_NHUM_VIEW_DIAM;
    for(
        iter = objects_around -> begin(RESOURCE);
        iter != objects_around -> end(RESOURCE); iter++
       )
    {
        Resource* res = dynamic_cast<Resource*>(*iter);
        if (res -> getSubtype()  == GRASS)
        {
            coords = res -> getCoords();
            if (distance < coords.getDistance(this -> getCoords()))
            {
                this -> aim = res;
                this -> angle = -1;
                distance = coords.getDistance(this -> getCoords());
            }
        }
    }
}

void NonHumanoid::feed(uint delta)
{
    if(this -> hunger - delta > 0)
    {
        this -> hunger -= delta;
    }
    else
    {
        hunger = 0;
    }
}
