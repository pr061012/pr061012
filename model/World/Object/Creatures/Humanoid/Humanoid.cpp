/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cassert>
#include <cstdlib>
#include <armadillo>
#include <assert.h>
#include "../../../../../common/Log/Log.h"

#include "Humanoid.h"
#include "../../../../../common/BasicDefines.h"
#include "../../../../../common/Random/Random.h"
#include "../../Resource/Resource.h"

// TODO:
//  * Add comments.
//  * Move (where it's needed) comparison between two doubles by comparison
//    between their difference and MATH_EPSILON const.
//
// FIXME:
//  * aim == 0?

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

uint Humanoid::CURRENT_HUM_ID = 0;

Humanoid::Humanoid(const DecisionMaker& dmaker) :
    Creature(HUMANOID, dmaker),
hum_id(CURRENT_HUM_ID++)
{
    int max_age = Random::int_range(HUM_AGE_MIN, HUM_AGE_MAX);

    // Initialize some inhereted things.
    this -> setMaxAge(max_age);
    this -> setAge(0);
    this -> setShapeSize(SZ_HUM_DIAM);
    this -> setShapeType(SHP_HUMANOID);
    this -> setViewArea(Shape(Vector(), SHP_HUM_VIEW_TYPE, SZ_HUM_VIEW_DIAM));

    // Set danger level
    setDangerLevel(HUM_DANGER_LEVEL);

    // Create visual_memory
    visual_memory = new ObjectHeap();

    // TODO: Randomly initialize humanoid's name.
    name = "Name";

    // Randomly initialize some values.
    max_sociability = Random::int_range(HUM_SOCIABILITY_MIN, HUM_SOCIABILITY_MAX);
    laziness        = Random::int_range(HUM_LAZINESS_MIN,    HUM_LAZINESS_MAX);
    bravery         = Random::int_range(HUM_BRAVERY_MIN,     HUM_BRAVERY_MAX);

    // Initialize other values.
    sociability    = 100 - max_sociability;
    need_in_points = 100;
    need_in_house  = 100;

    //Initialize of matrix of attr
    attrs(ATTR_HUNGER,0)         = 100 * hunger / max_hunger;
    attrs(ATTR_SLEEPINESS,0)     = 100 * sleepiness / max_sleepiness;
    attrs(ATTR_NEED_IN_HOUSE,0)  = need_in_house;
    attrs(ATTR_NEED_IN_POINTS,0) = 0; // need_in_points;
    attrs(ATTR_LAZINESS,0)       = laziness;
    attrs(ATTR_HEALTH,0)         = 100 * (100 - health) / max_health;
    attrs(ATTR_COMMUNICATION,0)  = 0; // 100 * sociability / max_sociability;
    attrs(ATTR_DANGER,0)         = danger;
    attrs(ATTR_NEED_IN_DESC,0)   = 0; // need_in_descendants;

    // Initialize home
    home = nullptr;

    // Initialize steps
    decr_endur_step = 0;
    age_steps       = CREAT_AGE_STEPS;
    common_steps    = CREAT_STEPS;
    danger_steps    = CREAT_DANGER_STEPS;
    desc_steps      = CREAT_DESC_STEPS;
    decr_sleep_step = 0;

    // Initialize decision
    this -> current_decision = NONE;
    this -> detailed_act     = SLEEP_ON_THE_GROUND;
}

Humanoid::~Humanoid()
{
    delete visual_memory;
}

//******************************************************************************
// ID.
//******************************************************************************

uint Humanoid::getHumanoidID() const
{
    return this -> hum_id;
}

//******************************************************************************
// ACTIONS.
//******************************************************************************

std::vector <Action>* Humanoid::getActions()
{
    this -> age_steps--;
    this -> common_steps--;
    this -> danger_steps--;
    this -> desc_steps--;
    if (!this -> decr_sleep_step)
    {
        this -> decr_sleep_step--;
    }

    // Updates parametr.
    if(age_steps == 0)
        updateAge();
    if(desc_steps == 0)
        updateNeedInDesc();
    if(common_steps == 0)
        updateCommonAttrs();
    if(danger_steps == 0)
        updateDanger();
    this -> actions.clear();

    // If decision is not actual humanoid makes new decision.
    if (!brains.isDecisionActual(attrs, current_decision))
    {
        current_decision = NONE;
    }

    // Make new decision and set aim and direction.
    if (current_decision == NONE)
    {
        current_decision = brains.makeDecision(attrs);
        direction_is_set = false;
        aim = nullptr;
        detailed_act = chooseAction(current_decision);
    }

    //**************************************************************************
    // DETAILED DECISION : RELAX_AT_HOME
    //**************************************************************************

    // First of all, we set direction (to home). If direction is seted
    // HUMANOID goes to home. If he is in home his health and endurance will
    // increase.

    if (detailed_act == RELAX_AT_HOME)
    {
        if ((aim != nullptr) && (!direction_is_set))
        {
            aim = home;
            direction_is_set = true;
        }

        if (this -> getCoords().getDistance(aim -> getCoords()) > MATH_EPSILON)
        {
            go(SLOW_SPEED);
            visualMemorize();
        }
        else
        {
            if (this -> health < 100 && common_steps == CREAT_STEPS)
            {
                this -> increaseHealth(CREAT_DELTA_HEALTH);
            }

            if (endurance < max_endurance)
            {
                endurance++;
            }
        }
    }

    //**************************************************************************
    // DETAILED DECISION : HUNT |        BAD FUNC !!!!!!!!!!
    //**************************************************************************

    if (detailed_act == HUNT)
    {
        go(SLOW_SPEED);
    }

    //**************************************************************************
    // DETAILED DECISION : FIND_FOOD
    //**************************************************************************

    // Searching for food inside humanoid visual memory. If it is founded he
    // eat it. In other case he just shuffles on the street and explores enviro-
    // ment.

    if (detailed_act == FIND_FOOD)
    {
        double min_dist = SZ_WORLD_VSIDE;
        ObjectHeap::const_iterator iter;
        for
        (
            iter = visual_memory -> begin(RESOURCE);
            iter != visual_memory -> end(RESOURCE); iter++
        )
        {
            Resource* res_food = dynamic_cast<Resource*>(*iter);
            if (res_food -> getSubtype() == RES_FOOD)
            {
                if (this -> getCoords().getDistance(res_food -> getCoords()) < min_dist)
                {
                    min_dist = this -> getCoords().getDistance(aim -> getCoords());
                    aim = res_food;
                }
            }
        }

        if (aim == nullptr)
        {
            go(SLOW_SPEED);
            visualMemorize();
        }
        else
        {

            if (this -> getCoords().getDistance(aim -> getCoords()) > MATH_EPSILON)
            {
                go(SLOW_SPEED);
                visualMemorize();
            }
            else
            {
                Action act(EAT_OBJ, this);
                act.addParticipant(aim);
                this -> actions.push_back(act);
            }
        }
    }

    //**************************************************************************
    // DETAILED DECISION : SLEEP_AT_HOME
    //**************************************************************************

    // First of all, humanoid comes home. After that we decrease his sleepiness
    // and increase endurance. We do it one time in HUM_DECR_SLEEP_STEPS steps.
    if (detailed_act == SLEEP_AT_HOME)
    {
        if (aim == nullptr)
        {
            aim = home;
        }

        if (this -> getCoords().getDistance(aim -> getCoords()) > MATH_EPSILON)
        {
            go(SLOW_SPEED);
            visualMemorize();
        }
        else
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
                if (endurance < max_endurance)
                {
                    endurance++;
                }
                decr_sleep_step = HUM_DECR_SLEEP_STEPS;
            }
            else
            {
                this -> decr_endur_step--;
            }
        }

    }

    //**************************************************************************
    // DETAILED DECISION : SLEEP_ON_THE_GROUND
    //**************************************************************************

    // Humanoid just increases endurance and decrease sleepiness
    if (detailed_act == SLEEP_ON_THE_GROUND)
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
            if (endurance < max_endurance)
            {
                endurance++;
            }

            decr_sleep_step = HUM_DECR_SLEEP_STEPS;
        }
        else
        {
            this -> decr_endur_step--;
        }
    }

    //**************************************************************************
    // DETAILED DECISION : MINE_RESOURSE
    //**************************************************************************

    // If we don't choose which resource humanoid want to mine, we check
    // his visual memory. After that humanoid come to this resource. If he
    // did not find any resource in his memory, he will just shuffle on the
    // street and memorize new object.

    if (detailed_act == MINE_RESOURSES)
    {
        if ((visual_memory != nullptr) && (aim == nullptr))
        {
            ObjectHeap::const_iterator iter;
            Vector coords;

            double distance = SZ_WORLD_HSIDE;
            for
            (
                iter = visual_memory -> begin(RESOURCE);
                iter != visual_memory -> end(RESOURCE); iter++
            )
            {
                Resource* res = dynamic_cast<Resource*>(*iter);
                if (res -> getSubtype()  == RES_BUILDING_MAT)
                {
                    coords = res -> getCoords();
                    if (distance < coords.getDistance(this -> getCoords()))
                    {
                        this -> aim = res;
                        distance = coords.getDistance(this -> getCoords());
                    }
                }
            }
        }

        if (aim == nullptr)
        {
             go(SLOW_SPEED);
             visualMemorize();
        }
        else
        {
            if (this -> getCoords().getDistance(aim -> getCoords()) > MATH_EPSILON)
            {
                go(SLOW_SPEED);
                visualMemorize();
            }
            else
            {
                Action act(MINE_OBJ, this);
                act.addParticipant(aim);
                act.addParam("res_index", 0);
                this -> actions.push_back(act);
                //detailed_act = BUILD_HOUSE;
            }
        }
    }

    //**************************************************************************
    // DETAILED DECISION : BUILD_HOUSE
    //**************************************************************************

    // Humanoid just asking controller for permission to increase health
    // of building.
    if (detailed_act == BUILD_HOUSE)
    {
        Action act(REGENERATE_OBJ, this);
        act.addParticipant(home);
        act.addParam("object_index", 0);
    }

    //**************************************************************************
    // DETAILED DECISION : TAKE_FOOD_FROM_INVENTORY
    //**************************************************************************

    // Humanoid searching for resource_food in inventory. After that he just
    // eat it.
    if (detailed_act == TAKE_FOOD_FROM_INVENTORY)
    {
        ObjectHeap::const_iterator iter;
        for(
            iter = inventory -> begin(RESOURCE);
            iter != inventory -> end(RESOURCE); iter++
           )
        {
            Resource* res_food = dynamic_cast<Resource*>(*iter);
            if (res_food -> getSubtype() == RES_FOOD)
            {
                this -> aim = res_food;
                break;
            }
        }
        Action act(EAT_OBJ, this);
        act.addParticipant(aim);
        this -> actions.push_back(act);
    }

    //**************************************************************************
    // DETAILED DECISION : FIGHT           BAD FUNC!!!!!!!
    //**************************************************************************

    if (detailed_act == FIGHT)
    {
        go(SLOW_SPEED);
    }

    //**************************************************************************
    // DETAILED DECISION : RUN_FROM_DANGER
    //**************************************************************************

    // Humanoid chooses direction to escape. After thart he run, if he doesn't
    // tired. In other case he just goes.
    if (detailed_act == RUN_FROM_DANGER)
    {
        chooseDirectionToEscape();
        if (this -> endurance > this -> max_endurance / 2)
        {
            if (decr_endur_step == 0)
            {
                 decr_sleep_step = HUM_DECR_ENDUR_STEPS;
            }
            go(FAST_SPEED);
            visualMemorize();
        }
        else
        {
            go(SLOW_SPEED);
            visualMemorize();
        }

    }

    //**************************************************************************
    // DETAILED DECISION : CHOOSE_PLACE_FOR_HOME            BAD FUNC!!!!!!!!!
    //**************************************************************************

    if(detailed_act == CHOOSE_PLACE_FOR_HOME)
    {
        Action act(CREATE_OBJ, this);
        // FIXME
        act.addParam<ObjectType>("obj_type", BUILDING);
        act.addParam<uint>("building_max_space", 3);
        act.addParam<uint>("building_max_health", 100);
        current_decision = NONE;
    }
    return &actions;
}

void Humanoid::receiveMessage(Message message)
{
}

void Humanoid::updateAge()
{
    this -> age++;
    this -> age_steps = CREAT_AGE_STEPS;

    if (this -> age == max_age)
        this -> health = 0;
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

DetailedHumAction Humanoid::chooseAction(CreatureAction action)
{
    DetailedHumAction result_act = SLEEP_ON_THE_GROUND;

    // Draft of father processing
    switch(action)
    {
        case EAT:               result_act = chooseWayToEat();      break;
        case SLEEP:             result_act = chooseWayToSleep();    break;
        case COMMUNICATE:                                           break;
        case RELAX:             result_act = chooseWayToRelax();    break;
        case WORK:                                                  break;
        case REALIZE_DREAM:                                         break;
        case ESCAPE:            result_act = chooseWayToEscape();   break;
        case BUILD:             result_act = chooseWayToBuild();    break;
        case REPRODUCE:                                             break;
        default:                                                    break;
    }

    return result_act;
}

DetailedHumAction Humanoid::chooseWayToRelax()
{
    if(home != 0)
    {
        return RELAX_AT_HOME;
    }

    return SLEEP_ON_THE_GROUND;
}

DetailedHumAction Humanoid::chooseWayToBuild()
{
    if (this -> home == 0)
    {
        return CHOOSE_PLACE_FOR_HOME;
    }
    else
    {
        ObjectHeap::const_iterator iter;
        for(
            iter = inventory -> begin(RESOURCE);
            iter != inventory -> end(RESOURCE); iter++
           )
        {
            Resource* res_build = dynamic_cast<Resource*>(*iter);
            if (res_build -> getSubtype() == RES_BUILDING_MAT)
            {
                return BUILD_HOUSE;
            }
        }
        return MINE_RESOURSES;
    }
}

DetailedHumAction Humanoid::chooseWayToEat()
{
    ObjectHeap::const_iterator iter;
    for(
        iter = inventory -> begin(RESOURCE);
        iter != inventory -> end(RESOURCE); iter++
       )
    {
        Resource* res_food = dynamic_cast<Resource*>(*iter);
        if (res_food -> getSubtype() == RES_FOOD)
        {
            this -> aim = res_food;
            return TAKE_FOOD_FROM_INVENTORY;
        }
    }

    {
        if ((force > 50 && bravery > 50) || (force > 80) || (bravery > 80))
        {
            return HUNT;
        }
        else
        {
            return FIND_FOOD;
        }

    }
}

DetailedHumAction Humanoid::chooseWayToSleep()
{
    if (this -> home != 0)
    {
        if
        (
        this -> getCoords().getDistance(this -> home -> getCoords()) <
        SLOW_SPEED * HUM_DECR_SLEEP_STEPS * (100 - sleepiness)
        )
        {
            return SLEEP_AT_HOME;
        }
    }
    return SLEEP_ON_THE_GROUND;

}

DetailedHumAction Humanoid::chooseWayToEscape()
{
    if ((force > 50 && bravery > 50) || (force > 80) || (bravery > 80))
    {
        return FIGHT;
    }
    else
    {
        return RUN_FROM_DANGER;
    }
}

void Humanoid::visualMemorize()
{

    ObjectHeap::const_iterator iter;
    for(
        iter = objects_around.begin(BUILDING);
        iter != objects_around.end(BUILDING); iter++
       )
    {
        this -> visual_memory -> push(*iter);
    }
    for(
        iter = objects_around.begin(RESOURCE);
        iter != objects_around.end(RESOURCE); iter++
       )
    {
         this -> visual_memory -> push(*iter);
    }
}

void Humanoid::setHome(Building *home)
{
    this -> home = home;
}

//**********************************************************
// DEBUG
//**********************************************************

uint Humanoid::getBravery() const
{
    return this -> bravery;
}

uint Humanoid::getNeedInHouse() const
{
    return this -> need_in_house;
}

Building* Humanoid::getHome() const
{
    return this -> home;
}

ObjectHeap* Humanoid::getVisMem() const
{
    return this -> visual_memory;
}

// returns current decision of humanoid
uint Humanoid::getCurrentDetailedAct() const
{
    return detailed_act;
}
