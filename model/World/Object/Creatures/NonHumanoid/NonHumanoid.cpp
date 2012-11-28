/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>

#include "NonHumanoid.h"
#include "../../Resource/Resource.h"
#include "../../../../../common/BasicDefines.h"
#include "../../../../../common/Math/Random.h"
#include "../../../../../common/Log/Log.h"
#include "../../../../../common/Math/DoubleComparison.h"
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
    this -> setReachArea(Shape(Vector(), SHP_NON_HUMANOID,
                               SZ_NHUM_DIAM * SZ_REACH_AREA_COEF));
    this -> setDangerLevel(DNGR_NON_HUMANOID);

    // Initialize of matrix of attr
    attrs(ATTR_HUNGER,0)         = 100 * getHunger() / getMaxHunger();
    attrs(ATTR_SLEEPINESS,0)     = 100 * getSleepiness() / getMaxSleepiness();
    attrs(ATTR_NEED_IN_HOUSE,0)  = 0;
    attrs(ATTR_NEED_IN_POINTS,0) = 0;
    attrs(ATTR_LAZINESS,0)       = 50; // our animal is very lazy,
                                        // so it always wants to relax
    attrs(ATTR_HEALTH,0)         = 100 * (100 - getHealth()) / getMaxHealth();
    attrs(ATTR_COMMUNICATION,0)  = 0;
    attrs(ATTR_DANGER,0)         = danger;
    attrs(ATTR_NEED_IN_DESC,0)   = 0; // need_in_descendants;

    //Initialize type
    subsubtype = COW;
}

NonHumanoid::~NonHumanoid()
{

}

//******************************************************************************
// INHERETED THINGS.
//******************************************************************************

std::string NonHumanoid::getTypeName() const
{
    return "non-humanoid";
}

std::string NonHumanoid::printObjectInfo() const
{
    return Creature::printObjectInfo();
}

//******************************************************************************
// NON-HUMANOID ACTIONS.
//******************************************************************************

std::vector <Action>* NonHumanoid::getActions()
{
// FIXME: Delete Log::NOTE();
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

    if (getHunger() == getMaxHunger())
    {
        this -> damage(CREAT_DELTA_HEALTH);
    }
    // Store the result of last action and clear actions.
    clearActions();

    if (!brains.isDecisionActual(attrs, current_decision))
    {
        current_decision = NONE;
    }

    //**************************************************************************
    // DECISION : NONE | OK
    //**************************************************************************
    if (current_decision == NONE)
    {
        Log::NOTE("NONE");
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
        Log::NOTE("SLEEP");
        // Check timesteps before wake up.
        if (decr_sleep_step == 0)
        {
            // Check sleepiness.
            if (getSleepiness() > 0)
            {
                decreaseSleepiness(1);
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
        Log::NOTE("RELAX");
        if (common_steps == CREAT_STEPS)
        {
            heal(CREAT_DELTA_HEALTH);
        }

        if (getEndurance() < getMaxEndurance())
        {
            increaseEndurance(1);
        }
        go(SLOW_SPEED);
    }

    //**************************************************************************
    // DECISION : EAT | OK
    //**************************************************************************
    else if (current_decision == EAT)
    {
        Log::NOTE("EAT");
        // If aim doesn't exist, then find grass.
        if (aim == nullptr)
        {
            findGrass();
        }

        // If aim exists, then...
        if (aim != nullptr)
        {
            // Check distance to aim.
            if (this -> getShape().hitTest(aim -> getShape()))
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
        if (getHunger() == 0)
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
        Log::NOTE("ESCAPE");
        if (
                this -> subsubtype == COW ||
                this -> subsubtype == GOOSE ||
                this -> subsubtype == SHEEP
           )
        {
            if (!direction_is_set)
            {
                chooseDirectionToEscape();
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
        Log::NOTE("REPRODUCE");
    }

    else if (current_decision == COMMUNICATE)
    {
        Log::NOTE("COMMUNICATE");
    }

    else if (current_decision == WORK)
    {
        Log::NOTE("WORK");
    }

    else if (current_decision == GATHER)
    {
        Log::NOTE("GATHER");
    }

    else if (current_decision == EXPLORE)
    {
        Log::NOTE("EXPLORE");
    }


    else if (current_decision == REALIZE_DREAM)
    {
        Log::NOTE("REALIZE_DREAM");
    }

    else if (current_decision == BUILD)
    {
        Log::NOTE("BUILD");
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
    increaseAge(1);
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
    increaseHunger(CREAT_DELTA_HUNGER);
    if (current_decision != SLEEP)
        increaseSleepiness(CREAT_DELTA_SLEEP);

    this -> attrs(ATTR_HUNGER,0)     = 100 * getHunger() / getMaxHunger();
    this -> attrs(ATTR_SLEEPINESS,0) = 100 * getSleepiness() / getMaxSleepiness();

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
            if (DoubleComparison::isLess(coords.getDistance(this -> getCoords()), distance))
            {
                this -> aim = res;
                direction_is_set = false;
                distance = coords.getDistance(this -> getCoords());
            }
        }
    }
}

