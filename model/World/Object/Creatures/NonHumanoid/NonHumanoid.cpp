/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include <cstdlib>


#include "../../../../../common/BasicDefines.h"
#include "../../../../../common/Math/Random.h"
#include "../../../../../common/Log/Log.h"
#include "../../../../../common/Math/DoubleComparison.h"
#include "../../Resource/Resource.h"
#include "../EDeprecatedAction.h"

#include "NonHumanoid.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

NonHumanoid::NonHumanoid(NonHumanoidType type, const DecisionMaker& dmaker) :
    Creature(NON_HUMANOID, dmaker),
    subsubtype(type),
    roam_steps(0)
{
    // Randomly initialise some values.
    int age = Random::int_range(NHUM_AGE_MIN, NHUM_AGE_MAX);

    // Initialise some inhereted things.
    this -> max_decr_sleep_step = NHUM_DECR_SLEEP_STEPS;
    this -> setAge(0);
    this -> setMaxAge(age);
    this -> setHunger(0.9 * this -> getMaxHunger());

    // Initialise type-dependent attributes.
    switch (subsubtype)
    {
        default: case COW: case COW_DEMON:
            this -> setShapeSize(SZ_NHUM_COW_DIAM);
            this -> setDangerLevel(DNGR_NHUM_COW);
            this -> setWeight(WGHT_NHUM_COW);
            this -> setNormalSpeed(SPD_NHUM_COW);
        break;

        case DRAGON:
            this -> setShapeSize(SZ_NHUM_DRAGON_DIAM);
            this -> setDangerLevel(DNGR_NHUM_DRAGON);
            this -> setWeight(WGHT_NHUM_DRAGON);
            this -> setNormalSpeed(SPD_NHUM_DRAGON);
        break;
    }

    this -> setShapeType(SHP_NHUM);

    // View and reach areas.
    this -> setViewArea(Shape(Vector(), SHP_NHUM_VIEW_TYPE, SZ_NHUM_VIEW_DIAM));
    this -> setReachArea(Shape(Vector(), SHP_NHUM, this -> getShape().getSize() * SZ_REACH_AREA_COEF));

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

std::string NonHumanoid::printObjectInfo(bool full) const
{
    std::stringstream ss;

    ss << Creature::printObjectInfo(full) <<
          insertSpaces("Type");
    switch (this -> subsubtype)
    {
        case COW: case COW_DEMON: ss << "cow";     break;
        case DRAGON:              ss << "dragon";  break;
        default:                  ss << "unknown"; break;
    }
    ss << std::endl;

    return ss.str();
}

//******************************************************************************
// NON-HUMANOID TYPE.
//******************************************************************************

NonHumanoidType NonHumanoid::getSubsubtype() const
{
    return this -> subsubtype;
}

//******************************************************************************
// NON-HUMANOID ACTIONS.
//******************************************************************************

std::vector<Action>* NonHumanoid::getActions()
{
    // FIXME: Implement it.
//    this -> desc_steps--;
//    if (desc_steps == 0)
//    {
//        updateNeedInDesc();
//    }

    // Update current state
    updateCommonAttrs();

    // Store the result of last action and clear actions.
    clearActions();

    // Cow demon will destroy this world!
    if (subsubtype == COW_DEMON)
    {
        ObjectHeap::const_iterator iter;
        for (iter = objects_around.begin(); iter != objects_around.end();
             iter++)
        {
            (*iter) -> markAsDestroyed();
        }
    }

    //**************************************************************************
    // FORCE ACTION RESETTING.
    //**************************************************************************

    // Checking whether current action is actual.
    if
    (
        !brains.isDecisionActual(attrs, current_action) ||
        (current_action == SLEEP && getSleepiness() == 0) ||
        (current_action == EAT && getHunger() == 0)
    )
    {
        current_action = NONE;
    }

    // Checking non-humanoid's sleepiness.
    if (getSleepiness() == getMaxSleepiness())
    {
        current_action = SLEEP;
    }

    // Reading messages.
    for (uint i = 0; i < messages.size(); i++)
    {
        // TODO: Need to add check (e.g. for dragons) whether can this non-
        //       humanoid fight with agressor or not.
        if (messages[i].getType() == UNDER_ATTACK)
        {
            current_action = ESCAPE;
            direction_is_set = false;
            aim = nullptr;
        }
    }
    messages.clear();

    //**************************************************************************
    // DECISION : NONE | OK
    //**************************************************************************

    if (current_action == NONE)
    {
        // Make decision.
        current_action = brains.makeDecision(attrs);

        // Zeroing everything else.
        direction_is_set = false;
        aim = nullptr;
    }

    //**************************************************************************
    // DECISION : SLEEP | OK
    //**************************************************************************

    if (current_action == SLEEP)
    {
        sleep();
    }

    //*************************************************************************
    // DECISION : RELAX | OK
    //**************************************************************************

    else if (current_action == RELAX)
    {
        relax();

        // Wherever I may roam...
        if (roam_steps == 0)
        {
            roam_steps = NHUM_ROAM_STEPS;
            direction_is_set = false;
        }
        roam_steps--;

        go(SLOW_SPEED);
    }

    //**************************************************************************
    // DECISION : EAT | OK
    //**************************************************************************

    else if (current_action == EAT)
    {
        // If aim was destroyed, reset it and try to find new.
        if (aim != nullptr && aim -> isDestroyed())
        {
            aim = nullptr;
        }

        // If aim doesn't exist trying to find food.
        if (aim == nullptr)
        {
            findFood();
        }

        // Bad. Trying to find someone to eat.
        if (aim == nullptr)
        {
            findVictim();
        }

        // So if aim was found, then...
        if (aim != nullptr)
        {
            // ... check distance to aim.
            if (getReachArea().hitTest(aim -> getShape()))
            {
                // If aim is resource, just eat it!
                if (aim -> getType() == RESOURCE)
                {
                    Action act(EAT_OBJ, this);
                    act.addParticipant(aim);
                    actions.push_back(act);
                }
                // Aim is creature, harm it.
                else if (aim -> getType() == CREATURE)
                {
                    fight();
                }
            }
            else
            {
                go(SLOW_SPEED);
            }
        }        
        else
        {
            // ... otherwise roaming and trying to find food.
            if (roam_steps == 0)
            {
                roam_steps = NHUM_ROAM_STEPS;
                direction_is_set = false;
            }
            roam_steps--;

            go(SLOW_SPEED);
        }

        // Check hunger state.
        if (getHunger() == 0)
        {
            current_action = NONE;
            direction_is_set = true;
            aim = nullptr;
        }
    }

    //**************************************************************************
    // DECISION : ESCAPE
    //**************************************************************************

    else if (current_action == ESCAPE)
    {
        if (!direction_is_set)
        {
            chooseDirectionToEscape();
        }

        go(SLOW_SPEED);
    }

    //**************************************************************************
    // DECISION : DEPRECATED DECISIONS
    //**************************************************************************

    else
    {
        throw EDeprecatedAction(NON_HUMANOID, current_decision);
    }

    return &actions;

}

void NonHumanoid::receiveMessage(Message message)
{
    this -> messages.push_back(message);
}

//******************************************************************************
// UPDATES.
//******************************************************************************

void NonHumanoid::updateNeedInDesc()
{
    // FIXME: Silly update.
    this -> need_in_descendants += NHUM_DELTA_NEED_IN_DESC;
    this -> attrs(ATTR_NEED_IN_DESC,0) = need_in_descendants;
    this -> desc_steps = CREAT_DESC_STEPS;
}

//******************************************************************************
// AUXILIARY FUNCTIONS.
//******************************************************************************

void NonHumanoid::findVictim()
{
    ObjectHeap::const_iterator iter;
    double distance = this -> getViewArea().getSize() / 2;

    // Only chosen one can eat other creatures.
    if (this -> subsubtype != DRAGON)
    {
        return;
    }

    // Trying to find victim in objects around.
    for
    (
        iter = objects_around.begin(CREATURE);
        iter != objects_around.end(CREATURE); iter++
    )
    {
        Creature* creat = dynamic_cast<Creature*>(*iter);

        bool is_eatable = false;

        if (creat -> getSubtype() == HUMANOID)
        {
            is_eatable = true;
        }
        else
        {
            NonHumanoid* nhum = dynamic_cast<NonHumanoid*>(creat);
            if (nhum -> getSubsubtype() != DRAGON)
            {
                is_eatable = true;
            }
        }

        if (is_eatable)
        {
            Vector coords = creat -> getCoords();

            // Check distance to found creature.
            if (DoubleComparison::isLess(coords.getDistance(this -> getCoords()), distance))
            {
                this -> aim = creat;
                direction_is_set = true;
                distance = coords.getDistance(this -> getCoords());
            }
        }
    }
}

void NonHumanoid::findFood()
{
    ObjectHeap::const_iterator iter;
    double distance = this -> getViewArea().getSize() / 2;

    // Trying to find resources in objects around.
    for
    (
        iter = objects_around.begin(RESOURCE);
        iter != objects_around.end(RESOURCE); iter++
    )
    {
        Resource* res = dynamic_cast<Resource*>(*iter);
        ResourceType type = res -> getSubtype();

        bool is_eatable = false;

        switch (this -> subsubtype)
        {
            case COW: case COW_DEMON:
                if (type == GRASS || type == BERRIES)
                {
                    is_eatable = true;
                }
            break;

            case DRAGON:
                if (type == MEAT)
                {
                    is_eatable = true;
                }
            break;
        }

        if (is_eatable)
        {
            Vector coords = res -> getCoords();

            // Check distance to found food.
            if (DoubleComparison::isLess(coords.getDistance(this -> getCoords()), distance))
            {
                this -> aim = res;
                direction_is_set = true;
                distance = coords.getDistance(this -> getCoords());
            }
        }
    }
}
