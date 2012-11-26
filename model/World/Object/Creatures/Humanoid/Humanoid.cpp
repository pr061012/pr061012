/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <armadillo>
#include <cassert>
#include <cstdlib>
#include <sstream>

#include "../../../../../common/Log/Log.h"

#include "Humanoid.h"
#include "../../../../../common/BasicDefines.h"
#include "../../../../../common/Math/Random.h"
#include "../../Resource/Resource.h"
#include "../../../../../common/Math/DoubleComparison.h"
// BAD
#include "../../../DecisionMaker/DecisionMaker.h"

// TODO:
//  * Add comments.
//  * Move (where it's needed) comparison between two doubles by comparison
//    between their difference and MATH_EPSILON const.
//
// FIXME:
//  * aim == 0?
using namespace std;
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
    this -> setReachArea(Shape(Vector(), SHP_HUMANOID,
                               SZ_HUM_DIAM * SZ_REACH_AREA_COEF));

    // Set danger level
    this -> setDangerLevel(DNGR_HUMANOID);

    // Create visual_memory
    visual_memory = new ObjectHeap();

    // TODO: Randomly initialize humanoid's name.
    name = "Name";

    // Randomly initialize some values.
    max_sociability = Random::int_range(HUM_SOCIABILITY_MIN, HUM_SOCIABILITY_MAX);
    laziness        = Random::int_range(HUM_LAZINESS_MIN,    HUM_LAZINESS_MAX);
    bravery         = Random::int_range(HUM_BRAVERY_MIN,     HUM_BRAVERY_MAX);

    // Initialize other values.
    sociability    = 0;  // BAD 100 - max_sociability;
    need_in_points = 0;  //100;
    need_in_house  = 70;

    //Initialize of matrix of attr.
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
// TYPE NAME.
//******************************************************************************

std::string Humanoid::getTypeName() const
{
    return "humanoid";
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
    if (this -> decr_sleep_step)
    {
        this -> decr_sleep_step--;
    }

    // Updates parametr.
    if(age_steps == 0)
    {
        updateAge();
    }
//    if(desc_steps == 0)
//        updateNeedInDesc();
    if(common_steps == 0)
    {
        updateCommonAttrs();
    }
    if(danger_steps == 0)
    {
        updateDanger();
    }

    // Update Need_in_house
    if (this -> home != nullptr)
    {
        if
        (
            100 * home -> getHealthPoints() / home -> getMaxHealthPoints()
            > 70
        )
        {
            need_in_house = 100 * home -> getHealthPoints()
            / home -> getMaxHealthPoints();
        }
        if (home -> getCompleteness())
        {
            this -> need_in_house = 0;

        }
        attrs(ATTR_NEED_IN_HOUSE,0) = need_in_house;
    }

    // check: is humanoid's home ok?
    if (home != nullptr && home -> isDestroyed())
    {
        home = nullptr;
        need_in_house = 70;
    }

    // Store the result of last action and clear actions
    clearActions();

    // If decision is not actual humanoid makes new decision.
    if (!brains.isDecisionActual(attrs, current_action))
    {
        current_decision = current_action;// BAD
        current_action = NONE;
        detailed_act     = SLEEP_ON_THE_GROUND;
    }

    // Make new decision and set aim and direction.
    if (current_action == NONE)
    {
        current_action = brains.makeDecision(attrs);
        this -> direction_is_set = false;
        aim = nullptr;
        detailed_act = chooseAction(current_action);
    }

    //**************************************************************************
    // DETAILED DECISION : RELAX_AT_HOME
    // First of all, we set direction (to home). If direction is set
    // HUMANOID goes to home. If he is in home his health and endurance will
    // increase.
    //**************************************************************************

    if (detailed_act == RELAX_AT_HOME)
    {
        if (aim == nullptr)
        {
            aim = home;
        }

        Shape reach_area = this -> getReachArea();
        reach_area.setCenter(this -> getCoords());
        if (!reach_area.hitTest(aim -> getShape()))
        {
            go(SLOW_SPEED);
            visualMemorize();
        }
        else
        {
            if (this -> health < 100 && common_steps == CREAT_STEPS)
            {
                this -> heal(CREAT_DELTA_HEALTH);
            }

            if (endurance < max_endurance)
            {
                endurance++;
            }
        }
    }

    //**************************************************************************
    // DETAILED DECISION : HUNT
    // FIXME
    // Create this action
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
            // skip all destroyed objects 
            if ((*iter) -> isDestroyed())
            {
                visual_memory -> remove(*iter);
                continue;
            }
            Resource* res_food = dynamic_cast<Resource*>(*iter);
            if (res_food -> getSubtype() == RES_FOOD)
            {
                if (this -> getCoords().getDistance(res_food -> getCoords()) < min_dist)
                {
                    aim = res_food;
                    min_dist = this -> getCoords().getDistance(aim -> getCoords());
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

            if (!this -> getShape().hitTest(aim -> getShape()))
            {
                go(SLOW_SPEED);
                visualMemorize();
            }
            else
            {
                Action act(EAT_OBJ, this);
                act.addParticipant(aim);
                this -> actions.push_back(act);
                current_action = NONE;
            }
        }
    }

    //**************************************************************************
    // DETAILED DECISION : SLEEP_AT_HOME
    // First of all, humanoid comes home. After that we decrease his sleepiness
    // and increase endurance. We do it one time in HUM_DECR_SLEEP_STEPS steps.
    //**************************************************************************

    if (detailed_act == SLEEP_AT_HOME)
    {
        if (aim == nullptr)
        {
            aim = home;
        }

        Shape reach_area = this -> getReachArea();
        reach_area.setCenter(this -> getCoords());
        if (!reach_area.hitTest(aim -> getShape()))
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
                    current_action = NONE;
                }
                if (endurance < max_endurance)
                {
                    endurance++;
                }
                decr_sleep_step = HUM_DECR_SLEEP_STEPS;
            }
        }

    }

    //**************************************************************************
    // DETAILED DECISION : SLEEP_ON_THE_GROUND | OK
    // Humanoid just increases endurance and decreases sleepiness
    //**************************************************************************

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
                current_action = NONE;
            }
            if (endurance < max_endurance)
            {
                endurance++;
            }

            decr_sleep_step = HUM_DECR_SLEEP_STEPS;
        }
    }

    //**************************************************************************
    // DETAILED DECISION : BUILD_HOUSE
    // Humanoid just asking controller for permission to increase health
    // of building.
    //**************************************************************************

    if (detailed_act == BUILD_HOUSE)
    {
        if (aim == nullptr)
        {
            aim = home;
        }
        Shape reach_area = this -> getReachArea();
        reach_area.setCenter(this -> getCoords());
        if (!reach_area.hitTest(aim -> getShape()))
        {
            go(SLOW_SPEED);
            visualMemorize();
        }
        else
        {
            Action act(REGENERATE_OBJ, this);
            act.addParticipant(home);
            act.addParam("object_index", 0);
            this -> actions.push_back(act);
            current_action = NONE;
        }
    }

    //**************************************************************************
    // DETAILED DECISION : MINE_RESOURSE | OK
    // If we don't choose which resource humanoid want to mine, we check
    // his visual memory. After that humanoid come to this resource. If he
    // did not find any resource in his memory, he will just shuffle on the
    // street and memorize new object.
    //**************************************************************************

    if (detailed_act == MINE_RESOURSES)
    {
        if ((visual_memory != nullptr) && (aim == nullptr))
        {
            ObjectHeap::const_iterator iter;
            for
            (
                iter = visual_memory -> begin(RESOURCE);
                iter != visual_memory -> end(RESOURCE); iter++
            )
            {
                // skip all destroyed objects
                if ((*iter) -> isDestroyed())
                {
                    visual_memory -> remove(*iter);
                    continue;
                }
                Resource* res = dynamic_cast<Resource*>(*iter);
                if (res -> getSubtype()  == RES_BUILDING_MAT)
                {
                    Vector coords;
                    double distance = SZ_WORLD_VSIDE;
                    coords = res -> getCoords();
                    if (distance > coords.getDistance(this -> getCoords()))
                    {
                        this -> aim = res;
                        distance = coords.getDistance(this -> getCoords());
                    }
                    this -> aim = res;
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
            Shape reach_area = this -> getReachArea();
            reach_area.setCenter(this -> getCoords());
            if (!reach_area.hitTest(aim -> getShape()))
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

                ObjectHeap::const_iterator iter;
                for(
                    iter = inventory -> begin(RESOURCE);
                    iter != inventory -> end(RESOURCE); iter++
                   )
                {
                    Resource* res = dynamic_cast<Resource*>(*iter);
                    if (res -> getSubtype() == RES_BUILDING_MAT)
                    {
                          detailed_act = BUILD_HOUSE;
                          aim = nullptr;
                    }
                }
            }
        }
    }

    //**************************************************************************
    // DETAILED DECISION : TAKE_FOOD_FROM_INVENTORY
    // Humanoid searching for resource_food in inventory. After that he just
    // eat it.
    //**************************************************************************

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
    // DETAILED DECISION : FIGHT
    // Fixme
    // Create this action
    //**************************************************************************

    if (detailed_act == FIGHT)
    {
        go(SLOW_SPEED);
    }

    //**************************************************************************
    // DETAILED DECISION : RUN_FROM_DANGER
    // Humanoid chooses direction to escape. After thart he run, if he doesn't
    // tired. In other case he just goes.
    //**************************************************************************

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
    // DETAILED DECISION : CHOOSE_PLACE_FOR_HOME
    // FIXME
    // Better way to choose place for home
    //**************************************************************************

    if(detailed_act == CHOOSE_PLACE_FOR_HOME)
    {
        Action act(CREATE_OBJ, this);
        act.addParam<ObjectType>("obj_type", BUILDING);
        // TODO: Ugly. Humanoid need to pick max_space and max_health values
        //       more accuratly.
        act.addParam<uint>("building_max_space",
                           Random::int_range(BLD_MAX_SPACE_MIN, BLD_MAX_SPACE_MAX));
        act.addParam<uint>("building_max_health",
                           Random::int_range(BLD_MAX_HEALTH_MIN, BLD_MAX_HEALTH_MAX));
        this -> actions.push_back(act);
        current_action = NONE;
    }

    return &actions;
}

void Humanoid::receiveMessage(Message message)
{
}

//******************************************************************************
// UPDATES
// We change attrs of our hum
//******************************************************************************

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
    if (this -> hunger < this -> max_hunger)
    {
        this -> hunger                 += CREAT_DELTA_HUNGER;
        this -> attrs(ATTR_HUNGER,0)    = 100 * hunger / max_hunger;
        if (hunger >= max_hunger)
        {
            this -> health = 0;
        }
    }

    if (this -> sleepiness < this -> max_sleepiness)
    {

        if (current_action != SLEEP)
        {
            this -> sleepiness += CREAT_DELTA_SLEEP;
            this -> attrs(ATTR_SLEEPINESS,0) =
                    100 * sleepiness / max_sleepiness;

            if (sleepiness >= max_sleepiness)
            {
                this -> detailed_act = SLEEP_ON_THE_GROUND;
            }
        }
    }
    // this -> sociability += HUM_DELTA_SOC;
    // this -> attrs(ATTR_COMMUNICATION,0)     = 100 * sociability / max_sociability;

    this -> common_steps = CREAT_STEPS;
    this -> attrs(ATTR_HEALTH,0) = 100 * (100 -health) / max_health;
}

//******************************************************************************
// CHOOSE ACTION
// Fuтction gets current action (decision) and called other function to make
// detailed decision.
//******************************************************************************

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

//******************************************************************************
// CHOOSE_WAY_TO_RELAX
// We just check: is his home exsist at all? If it doesn't exist... So, he is
// going to sleep on the ground.
//******************************************************************************
DetailedHumAction Humanoid::chooseWayToRelax()
{
    if(home != 0)
    {
        return RELAX_AT_HOME;
    }

    return SLEEP_ON_THE_GROUND;
}

//******************************************************************************
// CHOOSE_WAY_TO_BUILD
// We just check: is his home exsist at all? If it doesn't exist he is going to
// choose place for home. After that he will mine reciurse and build.
//******************************************************************************
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

//******************************************************************************
// CHOOSE_WAY_TO_EAT
// If he is bravery guy he will hunt. In other case, he will search food. But if
// he already has foon in inventory - he just takes it.
//******************************************************************************
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

//******************************************************************************
// CHOOSE_WAY_TO_SLLEP
// The best way to sleep is sleeping at home. But ih humanoid doesn't have home
// or he is too far from it he will sleep in the ground.
//******************************************************************************
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

//******************************************************************************
// CHOOSE_WAY_TO_ESCAPE
// If you are bravery and powerful you will fight. In other case - just run.
//******************************************************************************
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

// Puts new object in humanoid's memory
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

// Just setter
void Humanoid::setHome(Building *home)
{
    this -> home = home;
}

//******************************************************************************
// INHERETED THINGS.
//******************************************************************************

std::string Humanoid::printObjectInfo() const
{
    std::string output = Creature::printObjectInfo();

    std::stringstream ss;

    ss << "Detailed action\t\t";
    switch (detailed_act)
    {
        case HUNT:                     ss << "hunt";                     break;
        case TAKE_FOOD_FROM_INVENTORY: ss << "take food from inventory"; break;
        case FIND_FOOD:                ss << "find food";                break;
        case RELAX_AT_HOME:            ss << "relax at home";            break;
        case SLEEP_AT_HOME:            ss << "sleep at home";            break;
        case SLEEP_ON_THE_GROUND:      ss << "sleep on the ground";      break;
        case MINE_RESOURSES:           ss << "mine resource";            break;
        case BUILD_HOUSE:              ss << "build house";              break;
        case CHOOSE_PLACE_FOR_HOME:    ss << "choose place for home";    break;
        case FIGHT:                    ss << "fight";                    break;
        case RUN_FROM_DANGER:          ss << "run from danger";          break;
        default:                       ss << "unknown";                  break;
    }
    ss << "\n";

    ss << "Sociability\t\t"       << sociability << "/" << max_sociability <<
                                     std::endl <<
          "Bravery\t\t\t"         << bravery << std::endl <<
          "Laziness\t\t"          << laziness << std::endl <<
          "Need in house\t\t"     << need_in_house << std::endl <<
          "Need in points\t\t"    << need_in_points << std::endl <<
          "Home ID\t\t\t"         << (home == nullptr ? "none" :
                                      std::to_string(home -> getObjectID())) <<
                                     std::endl <<
          "Visual memory\t\t\n"   << visual_memory -> printIDs() << std::endl <<
          "Something\t\t"         << current_decision << std::endl <<
          "Matrix of attrs\t\t"   << attrs            << std::endl <<
          "Matrix of act\t\t"     << brains.getActMatrix(attrs) << endl;

    return output + ss.str();
}

//******************************************************************************
// DEBUG
//******************************************************************************

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

void Humanoid::setDetailedAction(DetailedHumAction det_action)
{
    this -> detailed_act = detailed_act;
}

// returns current decision of humanoid
uint Humanoid::getCurrentDetailedAct() const
{
    return detailed_act;
}

//******************************************************************************
// ADD TO INVENTORY
//******************************************************************************
void Humanoid::addToInventory(Object *obj)
{
    this -> inventory -> push(obj);
}
