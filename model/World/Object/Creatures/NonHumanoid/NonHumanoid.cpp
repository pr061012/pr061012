/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>

#include "NonHumanoid.h"
#include "../../Resource/Resource.h"
#include "../../../../../common/BasicDefines.h"
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
    this -> setShapeSize(SZ_NHUM_DIAM);
    this -> setShapeType(SHP_NON_HUMANOID);
    this -> setViewArea(Shape(Vector(), SHP_NHUM_VIEW_TYPE, SZ_NHUM_VIEW_DIAM));

    // Initialize of matrix of attr
    attrs(ATTR_HUNGER,0)         = 100 * hunger / max_hunger;
    attrs(ATTR_SLEEPINESS,0)     = 100 * sleepiness / max_sleepiness;
    attrs(ATTR_NEED_IN_HOUSE,0)  = 0;
    attrs(ATTR_NEED_IN_POINTS,0) = 0;
    attrs(ATTR_LAZINESS,0)       = 100; // our animal is very lazy,
                                        // so it always wants to relax
    attrs(ATTR_HEALTH,0)         = 100 * (100 - health) / max_health;
    attrs(ATTR_COMMUNICATION,0)  = 0;
    attrs(ATTR_DANGER,0)         = danger;
    attrs(ATTR_NEED_IN_DESC,0)   = need_in_descendants;

    //Initialize type
    subsubtype = COW;
}

NonHumanoid::~NonHumanoid()
{

}

//**************************************************************************
// NON_HUMANOID ACTIONS.
//**************************************************************************

std::vector <Action>* NonHumanoid::getActions()
{
    this -> age_steps--;
    this -> common_steps--;
    this -> danger_steps--;
    this -> desc_steps--;

    if (age_steps == 0)
        updateAge();
    if (desc_steps == 0)
        updateNeedInDesc();
    if (common_steps == 0)
        updateCommonAttrs();
    if (danger_steps == 0)
        updateDanger();

    // Clear actions.
    this -> actions.clear();

    if (!brains.isDecisionActual(attrs, current_decision))
    {
        current_decision = NONE;
    }

    //**************************************************************************
    // DECISION : NONE | OK
    //**************************************************************************
    if (current_decision == NONE)
    {
        // Make decision.
        current_decision = brains.makeDecision(attrs);

        direction_is_set = false;
        aim = nullptr;
    }

    //**************************************************************************
    // DECISION : SLEEP | OK
    //**************************************************************************
    if (current_decision == SLEEP)
    {
        // Check timesteps before wake up.
        if (decr_sleep_step == 0)
        {
            // Check sleepiness.
            if (sleepiness > 0)
            {
                sleepiness--;
            } 
            else
            {
                // If NH is awake, set NONE decision.
                current_decision = NONE;
            }

            // Set timesteps, before increase sleepness.
            decr_sleep_step = NHUM_DECR_SLEEP_STEPS;
        }
        else
        {
            decr_sleep_step--;
        }
    }

    //*************************************************************************
    // DECISION : RELAX | OK
    //**************************************************************************
    else if (current_decision == RELAX)
    {
        if (this -> health < max_health && common_steps == CREAT_STEPS)
        {
            this -> increaseHealth(CREAT_DELTA_HEALTH);
        }

        if (endurance < max_endurance)
        {
            endurance++;
        }
        go(SLOW_SPEED);
    }

    //**************************************************************************
    // DECISION : EAT | OK
    //**************************************************************************
    else if (current_decision == EAT)
    {
        // If aim isn't exist, then find grass.
        if (aim == nullptr)
        {
            findGrass();
        }

        // If aim is exist, then...
        if (aim != nullptr)
        {
            // Check distance to aim.
            if (this -> getCoords().getDistance(aim -> getCoords()) < MATH_EPSILON)
            {
                Action act(EAT_OBJ, this);
                act.addParticipant(aim);
                actions.push_back(act);
            }
            else
            {
                go(SLOW_SPEED);
            }
        }
        else
        {
            go(SLOW_SPEED);
        }

        // Check hunger state.
        if (hunger == 0)
        {
            this -> current_action = NONE;
            direction_is_set = false;
            aim = nullptr;
        }
    }

    //**************************************************************************
    // DECISION : ESCAPE
    //**************************************************************************
    else if (current_decision == ESCAPE)
    {
        if (
                this -> subsubtype == COW ||
                this -> subsubtype == GOOSE ||
                this -> subsubtype == SHEEP
           )
        {
            if (angle == -1)
            {
                angle = Random::double_num(2 * M_PI);
            }
            go(SLOW_SPEED);
        }
        else
        {

        }

    }

    //**************************************************************************
    // DECISION : REPRODUCE
    //**************************************************************************
    else if (current_decision == REPRODUCE)
    {

    }

    return &actions;

}

void NonHumanoid::receiveMessage(Message message)
{
}

//**************************************************************************
// NON-HUMANOID'S LOGICS.
//**************************************************************************

//**************************************************************************
// UPDATES
//**************************************************************************
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
    if (hunger == max_hunger)
    {
        this -> decreaseHealth(CREAT_DELTA_HEALTH);
    }
    if (current_decision != SLEEP)
        this -> sleepiness += CREAT_DELTA_SLEEP;

    this -> attrs(ATTR_HUNGER,0)     = 100 * hunger / max_hunger;
    this -> attrs(ATTR_SLEEPINESS,0) = 100 * sleepiness / max_sleepiness;

    this -> common_steps = CREAT_STEPS;
}

//**************************************************************************
// AUXILIARY FUNTIONS
//**************************************************************************
void NonHumanoid::findGrass()
{
    ObjectHeap::const_iterator iter;
    Vector coords;
    double distance = SZ_NHUM_VIEW_DIAM;

    // Find grass in around objects.
    for(
        iter = objects_around.begin(RESOURCE);
        iter != objects_around.end(RESOURCE); iter++
       )
    {
        Resource* res = dynamic_cast<Resource*>(*iter);
        if (res -> getSubtype() == RES_FOOD)
        {
            coords = res -> getCoords();
            // Check distance to grass.
            if (coords.getDistance(this -> getCoords()) > distance)
            {
                this -> aim = res;
                direction_is_set = false;
                distance = coords.getDistance(this -> getCoords());
            }
        }
    }
}

