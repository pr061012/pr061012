/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include <cstdlib>

#include "NonHumanoid.h"

#include "../../../../../common/BasicDefines.h"
#include "../../../../../common/Math/Random.h"
#include "../../../../../common/Log/Log.h"
#include "../../../../../common/Math/DoubleComparison.h"

#include "../../Resource/Resource.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

NonHumanoid::NonHumanoid(const DecisionMaker & dmaker) :
    Creature(NON_HUMANOID, dmaker)
{
    // Randomly initialise some values.
    int age = Random::int_range(NHUM_AGE_MIN, NHUM_AGE_MAX);

    // Initialise some inhereted things.
    this -> max_decr_sleep_step = NHUM_DECR_SLEEP_STEPS;
    this -> setAge(0);
    this -> setMaxAge(age);
    this -> setShapeSize(SZ_NHUM_DIAM);
    this -> setShapeType(SHP_NON_HUMANOID);
    this -> setViewArea(Shape(Vector(), SHP_NHUM_VIEW_TYPE, SZ_NHUM_VIEW_DIAM));
    this -> setReachArea(Shape(Vector(), SHP_NON_HUMANOID,
                               SZ_NHUM_DIAM * SZ_REACH_AREA_COEF));
    this -> setDangerLevel(DNGR_NON_HUMANOID);
    this -> setWeight(WGHT_NON_HUMANOID);

    // Initialise of matrix of attributes.
    attrs(ATTR_HUNGER, 0)         = 100 * getHunger() / getMaxHunger();
    attrs(ATTR_SLEEPINESS, 0)     = 100 * getSleepiness() / getMaxSleepiness();
    attrs(ATTR_NEED_IN_HOUSE, 0)  = 0;
    attrs(ATTR_NEED_IN_POINTS, 0) = 0;
    attrs(ATTR_LAZINESS, 0)       = 50; // our animal is very lazy,
                                        // so it always wants to relax
    attrs(ATTR_HEALTH, 0)         = 100 * (100 - getHealth()) / getMaxHealth();
    attrs(ATTR_COMMUNICATION, 0)  = 0;
    attrs(ATTR_DANGER, 0)         = danger;
    attrs(ATTR_NEED_IN_DESC, 0)   = 0; // need_in_descendants;

    // Initialise type.
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
    this -> desc_steps--;

    if (desc_steps == 0)
    {
        updateNeedInDesc();
    }

    // Update current state
    updateCommonAttrs();

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
        sleep();
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
            direction_is_set = false;
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

        if (!direction_is_set)
        {
            chooseDirectionToEscape();
        }
        go(SLOW_SPEED);
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
    MessageType msg_type = message.getType();

    if (msg_type == UNDER_ATTACK)
    {
        chooseDirectionToEscape();
        //go(SLOW_SPEED);
    }
}

//******************************************************************************
// UPDATES
//******************************************************************************
void NonHumanoid::updateNeedInDesc()
{
    this -> need_in_descendants += NHUM_DELTA_NEED_IN_DESC;
    this -> attrs(ATTR_NEED_IN_DESC,0) = need_in_descendants;
    this -> desc_steps = CREAT_DESC_STEPS;
}

//******************************************************************************
// AUXILIARY FUNTIONS
//******************************************************************************
void NonHumanoid::findGrass()
{
    ObjectHeap::const_iterator iter;
    Vector coords;
    double distance = SZ_NHUM_VIEW_DIAM;

    // Find grass in around objects heap.
    for
    (
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
