/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <armadillo>
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <string>

#include "../../../../../common/Log/Log.h"

#include "Humanoid.h"
#include "../../../../../common/BasicDefines.h"
#include "../../../../../common/Math/Random.h"
#include "../../Resource/Resource.h"
#include "../../../../../common/Math/DoubleComparison.h"
// BAD
#include "../../../DecisionMaker/DecisionMaker.h"

// TODO:
//  Errors
//  Searching for resourse
//  Relax/FindFood

using namespace std;
//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

uint Humanoid::CURRENT_HUM_ID = 0;

Humanoid::Humanoid(const DecisionMaker& dmaker) :
    Creature(HUMANOID, dmaker),
    hum_id(CURRENT_HUM_ID++),
    inventory(new ObjectHeap)
{
    int max_age = Random::int_range(HUM_AGE_MIN, HUM_AGE_MAX);

    // Initialize some inhereted things.
    max_decr_sleep_step = HUM_DECR_SLEEP_STEPS;
    this -> setMaxAge(max_age);
    this -> setAge(0);
    this -> setShapeSize(SZ_HUM_DIAM);
    this -> setShapeType(SHP_HUMANOID);
    this -> setViewArea(Shape(Vector(), SHP_HUM_VIEW_TYPE, SZ_HUM_VIEW_DIAM));
    this -> setReachArea(Shape(Vector(), SHP_HUMANOID,
                               SZ_HUM_DIAM * SZ_REACH_AREA_COEF));
    this -> setWeight(WGHT_HUMANOID);

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
    attrs(ATTR_HUNGER,0)         = 100 * getHunger() / getMaxHunger();
    attrs(ATTR_SLEEPINESS,0)     = 100 * getSleepiness() / getMaxSleepiness();
    attrs(ATTR_NEED_IN_HOUSE,0)  = need_in_house;
    attrs(ATTR_NEED_IN_POINTS,0) = 0; // need_in_points;
    attrs(ATTR_LAZINESS,0)       = laziness;
    attrs(ATTR_HEALTH,0)         = 100 * (100 - getHealth()) / getMaxHealth();
    attrs(ATTR_COMMUNICATION,0)  = 0; // 100 * sociability / max_sociability;
    attrs(ATTR_DANGER,0)         = danger;
    attrs(ATTR_NEED_IN_DESC,0)   = 0; // need_in_descendants;

    // Initialize home
    home = nullptr;

    // Initialize steps
    decr_endur_step = 0;

    this -> detailed_act     = SLEEP_ON_THE_GROUND;
    steps_to_choose_place = 0; // BAD

}

Humanoid::~Humanoid()
{
    delete inventory;
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
    // Checking: is steps greater than 0? And decrease them.
    if (this -> desc_steps)
    {
        this -> desc_steps--;
    }

    // Updates parametr.
//    if(desc_steps == 0)
//        updateNeedInDesc();
    updateCommonAttrs();

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

    // Update attrs
    if (current_action == EAT)
    {
        if (getHunger() < 10) // FIXME magic const
        {
            attrs(ATTR_HUNGER, 0) = getHunger();
            current_action = NONE;
        }
    }
    if (current_action== SLEEP)
    {
        if (getSleepiness() == 0)
        {
            attrs(ATTR_SLEEPINESS, 0) = 0;
            current_action = NONE;
        }
    }

    // Force him to sleep if he really want it
    if (getSleepiness() == getMaxSleepiness())
    {
        current_action = SLEEP;
        detailed_act   = SLEEP_ON_THE_GROUND;
    }

    // check: is humanoid's home ok?
    if (home != nullptr && home -> isDestroyed())
    {
        home = nullptr;
        need_in_house = 70;// FIXME
    }

    // Get current errors
    current_errors.clear();
    current_errors = errorProcess();

    // Store the result of last action and clear actions
    clearActions();
    cleanInventory();

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

    // Get messages
    messageProcess();

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
            relax();
        }
    }

    //**************************************************************************
    // DETAILED DECISION : HUNT
    // FIXME. Nobody put food in inventory
    // First of all, he searching for victim in objects around. If he has
    // founded his sacrifice, he just hunts. If other case he goes in random
    // way serching for sacrifice.
    //**************************************************************************

    if (detailed_act == HUNT)
    {
        double min_dist = SZ_WORLD_VSIDE;
        ObjectHeap::const_iterator iter;
        for
        (
            iter = objects_around.begin(CREATURE);
            iter != objects_around.end(CREATURE); iter++
        )
        {
            // FIXME You don't use any of Creature's feature, why you make dynamic_cast?
            Creature* creat = dynamic_cast<Creature*>(*iter);
            if
            (
                this -> getCoords().getDistance(creat -> getCoords()) < min_dist
                && this -> getDangerLevel() > creat -> getDangerLevel()
            )
            {
                aim = creat;
                min_dist = this -> getCoords().getDistance(aim -> getCoords());
            }
        }
        if (aim == nullptr)
        {
            go(SLOW_SPEED);
            visualMemorize();
        }
        else
        {
            hunt();
            if (100* getHunger() / getMaxHunger() > 60)
            {
                detailed_act = FIND_FOOD;
            }
            if (aim -> isDestroyed())
            {
                detailed_act = TAKE_FOOD_FROM_INVENTORY;
            }
        }
    }

    //**************************************************************************
    // DETAILED DECISION : FIND_FOOD
    // Searching for food inside humanoid visual memory. If it is founded he
    // eat it. In other case he just shuffles on the street and explores enviro-
    // ment.
    //**************************************************************************

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
            sleep();
            if (getSleepiness() == 0)
            {
                current_action = NONE;
            }
        }

    }

    //**************************************************************************
    // DETAILED DECISION : SLEEP_ON_THE_GROUND | OK
    // Humanoid just increases endurance and decreases sleepiness
    //**************************************************************************

    if (detailed_act == SLEEP_ON_THE_GROUND)
    {
        sleep();
        if (getSleepiness() == 0)
        {
            current_action = NONE;
        }
    }

    //**************************************************************************
    // DETAILED DECISION : BUILD_HOUSE
    // Humanoid just asking controller for permission to increase health
    // of building.
    //**************************************************************************

    if (detailed_act == BUILD_HOUSE)
    {
        // FIXME Program can enter here with home == nullptr
        if (home) {
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
            double distance = SZ_WORLD_VSIDE;
            for
            (
                iter = visual_memory -> begin(RESOURCE);
                iter != visual_memory -> end(RESOURCE); iter++
            )
            {
                // skip all destroyed objects
                if ((*iter) -> isDestroyed())
                {
                    continue;
                }
                Resource* res = dynamic_cast<Resource*>(*iter);
                if (res -> getSubtype()  == RES_BUILDING_MAT)
                {
                    Vector coords;
                    coords = res -> getCoords();
                    if (distance > coords.getDistance(this -> getCoords()))
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
        if (aim != nullptr)
        {
            Action act(EAT_OBJ, this);
            act.addParticipant(aim);
            this -> actions.push_back(act);
        }
    }

    //**************************************************************************
    // DETAILED DECISION : FIGHT
    // Fixme
    // Create this action
    //**************************************************************************

    if (detailed_act == FIGHT)
    {
        fight();
    }

    //**************************************************************************
    // DETAILED DECISION : RUN_FROM_DANGER
    // Humanoid chooses direction to escape. After thart he run, if he doesn't
    // tired. In other case he just goes.
    //**************************************************************************

    if (detailed_act == RUN_FROM_DANGER)
    {
        chooseDirectionToEscape();
        if (getEndurance() > getMaxEndurance() / 2)
        {
            // FIXME What is this?
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
        direction_is_set = true; // BAD

    }

    //**************************************************************************
    // DETAILED DECISION : CHOOSE_PLACE_FOR_HOME
    // FIXME
    // Better way to choose place for home
    //**************************************************************************

    if(detailed_act == CHOOSE_PLACE_FOR_HOME)
    {
        if(!steps_to_choose_place)
        {
            steps_to_choose_place = 20;
            direction_is_set = true;
            this -> special_angle = Random::double_num(2*M_PI);
        }
        bool is_all_ok = true;
        for (uint i = 0; i < current_errors.size(); i++)
        {
            if (current_errors[i] == NO_PLACE_TO_PLACE_OBJ_ON)
            {
                this -> angle = special_angle;
                this -> direction_is_set = true;
                go(SLOW_SPEED);
                is_all_ok = false;
                steps_to_choose_place--;
            }
        }
        if(is_all_ok)
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
    }

    return &actions;
}

//******************************************************************************
// MESSAGES
//******************************************************************************

// Receiving of messages. Used in controller.
void Humanoid::receiveMessage(Message message)
{
    this -> msgs.push_back(message);
}

// Processing of messages
void Humanoid::messageProcess()
{
    for (uint i=0; i < msgs.size(); i++)
    {
        if (msgs[i].getType() == UNDER_ATTACK)
        {
            this -> current_action = ESCAPE;
            aim = msgs[i].getSender();
            detailed_act = chooseWayToEscape();
        }
    }
}

//******************************************************************************
// ACTION'S ERRORS
// Processing of action's errors.
//******************************************************************************
std::vector<ActionError> Humanoid::errorProcess()
{
    std::vector<ActionError> error;
    for (uint i=0; i < actions.size(); i++)
    {
        if (actions[i].isSucceeded())
        {
            this -> need_in_descendants -= 10;
            error.push_back(NO_ERROR);
            break;
        }
        error.push_back(actions[i].getError());
    }
    return error;

}

//******************************************************************************
// UPDATES
// We change attrs of our hum
//******************************************************************************

void Humanoid::updateNeedInDesc()
{
    this -> need_in_descendants += HUM_DELTA_NEED_IN_DESC; // need 0 NHum dont need in descendant
    this -> attrs(ATTR_NEED_IN_DESC,0) = need_in_descendants; // we dont need in transformation this attr
    this -> desc_steps = CREAT_DESC_STEPS;
}

//TODO Make separate update for sciability
    // this -> sociability += HUM_DELTA_SOC;
    // this -> attrs(ATTR_COMMUNICATION,0)     = 100 * sociability / max_sociability;
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
    if(home != nullptr)
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
        if
        (
            ((getForce() > 50 && bravery > 50) || (getForce() > 80)
            || (bravery > 80)) && 100 * getHunger() / getMaxHunger() < 60 // BAD - magic const
        )
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
    if (this -> home != nullptr)
    {
            return SLEEP_AT_HOME;
    }
    return SLEEP_ON_THE_GROUND;

}

//******************************************************************************
// CHOOSE_WAY_TO_ESCAPE
// If you are bravery and powerful you will fight. In other case - just run.
//******************************************************************************
DetailedHumAction Humanoid::chooseWayToEscape()
{
    if ((getForce() > 50 && bravery > 50) || (getForce() > 80) || (bravery > 80))
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

std::string Humanoid::printObjectInfo(bool full) const
{
    std::stringstream ss;
    ss << Creature::printObjectInfo(full);

    ss << insertSpaces("Detailed action");
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
    ss << std::endl;

    ss << insertSpaces("Sociability")                << sociability << "/" << max_sociability << std::endl <<
          insertSpaces("Bravery")                    << bravery << std::endl <<
          insertSpaces("Laziness")                   << laziness << std::endl;

    if (full)
    {
        ss << insertSpaces("Need in house")          << need_in_house << std::endl <<
              insertSpaces("Need in points")         << need_in_points << std::endl;
    }

    ss << insertSpaces("Home ID")                    << (home == nullptr ? "none" : std::to_string(home -> getObjectID())) << std::endl;

    if (full)
    {
        ss << insertSpaces("Inventory")              << std::endl << inventory -> printIDs();
        ss << insertSpaces("Visual memory")          << std::endl << visual_memory -> printIDs() <<
              insertSpaces("Steps for choose place") << steps_to_choose_place << std::endl;
    }

    return ss.str();
}

//******************************************************************************
// INVENTORY
//******************************************************************************

// Adds object to inventory.
void Humanoid::addToInventory(Object *obj)
{
    // Resources should be stacked together
    if (obj -> getType() == RESOURCE)
    {
        ResourceType subtype = dynamic_cast<Resource*>(obj) -> getSubtype();
        for (ObjectHeap::iterator i = inventory -> begin(RESOURCE);
             i != inventory -> end(RESOURCE); i++)
        {
            if (dynamic_cast<Resource*>(*i) -> getSubtype() == subtype)
            {
                (*i) -> heal(obj -> getHealthPoints());
                obj -> markAsDestroyed();
                return;
            }
        }
    }

    // If there are no resources of this type, or it's something else, just push it.
    this -> inventory -> push(obj);
}

// Clear inventory from destroyed objects.
void Humanoid::cleanInventory()
{
    // First place them in buffer.
    std::vector<Object*> buffer;
    for (ObjectHeap::iterator i = inventory -> begin();
         i != inventory -> end(); i++)
    {
        if ((*i) -> isDestroyed())
        {
            buffer.push_back(*i);
        }
    }

    // Then remove them from inventory.
    for (uint i = 0; i < buffer.size(); i++)
    {
        inventory -> remove(buffer[i]);
    }
}

// Remove object from inventory.
void Humanoid::removeFromInventory(Object * obj)
{
    inventory -> remove(obj);
}

ObjectHeap * Humanoid::getInventory()
{
    return this -> inventory;
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

void Humanoid::setDetailedAction(DetailedHumAction detailed_act)
{
    this -> detailed_act = detailed_act;
}

// returns current decision of humanoid
uint Humanoid::getCurrentDetailedAct() const
{
    return detailed_act;
}
