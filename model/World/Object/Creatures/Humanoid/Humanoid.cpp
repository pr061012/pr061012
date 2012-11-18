/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>
#include <armadillo>

#include "Humanoid.h"
#include "../../../../../common/BasicDefines.h"
#include "../../../../../common/Random/Random.h"
#include "../../Resource/Resource.h"


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
    this -> setShapeSize(SZ_HUM_DIAM);
    this -> setShapeType(SHP_HUMANOID);
    this -> setViewArea(Shape(Vector(), SHP_HUM_VIEW_TYPE, SZ_HUM_VIEW_DIAM));

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
    attrs(ATTR_NEED_IN_POINTS,0) = need_in_points;
    attrs(ATTR_LAZINESS,0)       = laziness;
    attrs(ATTR_HEALTH,0)         = 100 * (100 - health) / max_health;
    attrs(ATTR_COMMUNICATION,0)  = 100 * sociability / max_sociability;
    attrs(ATTR_SAFETY,0)         = safety;
    attrs(ATTR_NEED_IN_DESC,0)   = need_in_descendants;

    // Initialize home
    home = 0;
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
    if (!this -> decr_sleep_step)
    {
        this -> decr_sleep_step--;
    }
    if (!this -> decr_endur_step)
    {
        this -> decr_endur_step--;
    }

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

    if (detailed_act == RELAX_AT_HOME)
    {
        if (angle == -1)
        {
            aim = home;
            angle = setDirection();
        }

        if (this -> getCoords().getDistance(aim -> getCoords()) > MATH_EPSILON)
        {
            Action act(GO, this);
            act.addParam<double>("angle", angle);
            act.addParam<SpeedType>("speed", SLOW_SPEED);
            visualMemorize();
            this -> actions.push_back(act);
        }
        else
        {
            if (this -> health < 100 && common_steps == CREAT_STEPS) //freq incr health
                this -> increaseHealth(CREAT_DELTA_HEALTH);
            if (endurance < max_endurance)
            {
                endurance++;
            }
        }
    }

    if (detailed_act == HUNT)
    {

    }

    if (detailed_act == FIND_FOOD)
    {
        double min_dist = SZ_WORLD_VSIDE;
        ObjectHeap::const_iterator iter;
        for(
            iter = visual_memory -> begin(RESOURCE);
            iter != visual_memory -> end(RESOURCE); iter++
           )
        {
            Resource* res_food = dynamic_cast<Resource*>(*iter);
            if (res_food -> getSubtype() == RES_FOOD)
            {
                if (this -> getCoords().getDistance(aim -> getCoords()) < min_dist)
                {
                    min_dist = this -> getCoords().getDistance(aim -> getCoords());
                    aim = res_food;
                }
            }
        }
        if (angle == -1)
        {
            angle = setDirection();
        }
        if (this -> getCoords().getDistance(aim -> getCoords()) > MATH_EPSILON)
        {
            Action act(GO, this);
            act.addParam<double>("angle", angle);
            visualMemorize();
            act.addParam<SpeedType>("speed", SLOW_SPEED);
            this -> actions.push_back(act);
        }
        else
        {
            Action act(EAT_OBJ, this);
            act.addParticipant(aim);
            this -> actions.push_back(act);
        }
    }

    if (detailed_act == SLEEP_AT_HOME)
    {
        if (angle == -1)
        {
            aim = home;
            angle = setDirection();
        }
        if (this -> getCoords().getDistance(aim -> getCoords()) > MATH_EPSILON)
        {
            Action act(GO, this);
            act.addParam<double>("angle", angle);
            visualMemorize();
            act.addParam<SpeedType>("speed", SLOW_SPEED);
            this -> actions.push_back(act);
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
        }

    }

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
    }

    if (detailed_act == MINE_RESOURSES)
    {

    }

    if (detailed_act == BUILD_HOUSE)
    {

    }

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

    if (detailed_act == FIGHT)
    {

    }

    if (detailed_act == RUN_FROM_DANGER)
    {
        chooseDirectionToEscape();
        Action act(GO, this);
        act.addParam<double>("angle", angle);
        visualMemorize();
        if (this -> endurance > this -> max_endurance / 2)
        {
            act.addParam<SpeedType>("speed", FAST_SPEED);
            if (decr_endur_step == 0)
            {
                 decr_sleep_step = HUM_DECR_ENDUR_STEPS;
            }
            this -> actions.push_back(act);
        }
        else
        {
            act.addParam<SpeedType>("speed", SLOW_SPEED);
            visualMemorize();
        }

    }

    if(detailed_act == CHOOSE_PLACE_FOR_HOME)
    {
        Action act(CREATE_OBJ, this);
        // FIXME
        act.addParam<ObjectType>("obj_type", BUILDING);
        act.addParam<uint>("building_max_space", 3);
        act.addParam<uint>("building_max_health", 100);
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
    DetailedHumAction result_act = RELAX_AT_HOME;

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
    return RELAX_AT_HOME;
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
    if
    (
        this -> getCoords().getDistance(this -> home -> getCoords()) <
        SLOW_SPEED * HUM_DECR_SLEEP_STEPS * (100 - sleepiness)
    )
    {
        return SLEEP_AT_HOME;
    }
    else
    {
        return SLEEP_ON_THE_GROUND;
    }
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
        iter = inventory -> begin(BUILDING);
        iter != inventory -> end(BUILDING); iter++
       )
    {
        Building* build = dynamic_cast<Building*>(*iter);
        this -> visual_memory -> push(build);
    }
    for(
        iter = inventory -> begin(RESOURCE);
        iter != inventory -> end(RESOURCE); iter++
       )
    {
        Resource* res = dynamic_cast<Resource*>(*iter);
        this -> visual_memory -> push(res);
    }
}
