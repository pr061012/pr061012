/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cmath>

#include "Creature.h"
#include "../../../../common/BasicDefines.h"
#include "../../../../common/Math/Random.h"
#include "../Weather/Weather.h"


//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Creature::Creature(CreatureType type, const DecisionMaker & dmaker) :
    Object(CREATURE),
    subtype(type),
    goal(0),
    inventory(new ObjectHeap),
    current_action(NONE),
    attrs(arma::mat(DM_ATR_CONST, 1)),
    brains(dmaker),

    // some general attributes
    force(Random::int_range(CREAT_FORCE_MIN,    CREAT_FORCE_MAX)),
    max_endurance(Random::int_range(CREAT_ENDURANCE_MAX,  CREAT_ENDURANCE_MAX)),
    endurance(max_endurance),
    max_health(Random::int_range(CREAT_HEALTH_MIN, CREAT_HEALTH_MAX)),
    health(max_health),
    max_sleepiness(Random::int_range(CREAT_SLEEPINESS_MIN, CREAT_SLEEPINESS_MAX)),
    sleepiness (100 - max_sleepiness),
    max_hunger(Random::int_range(CREAT_HUNGER_MIN,     CREAT_HUNGER_MAX)),
    hunger(100 - max_hunger),
    
    // needs
    need_in_descendants(0),
    danger(0),               // we need in function to calculate it
                             // different for HUM and NON_HUM?
                             //
    // step counters
    common_steps(CREAT_STEPS),
    age_steps(CREAT_AGE_STEPS),
    desc_steps(CREAT_DESC_STEPS),
    danger_steps(CREAT_DANGER_STEPS),
    decr_sleep_step(0),
    
    // direction
    angle(0),
    direction_is_set(false),
    aim(0),
    current_decision(NONE)
{
}

Creature::~Creature()
{
    delete inventory;
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************
CreatureType Creature::getSubtype() const
{
    return this -> subtype;
}

void Creature::setObjectsAround(ObjectHeap objects_around)
{
    this -> objects_around = objects_around;
}

ObjectHeap * Creature::getObjectsAround()
{
    return &(this -> objects_around);
}

void Creature::setViewArea(Shape view_area)
{
    this -> view_area = view_area;
}

Shape Creature::getViewArea()
{
    return this -> view_area;
}

ObjectHeap * Creature::getInventory()
{
    return this -> inventory;
}

//**********************************************************
// AGE
//**********************************************************

void Creature::setAge(uint age)
{
    this -> age = age;
}

uint Creature::getAge()
{
    return this -> age;
}

void Creature::setMaxAge(uint max_age)
{
    this -> max_age = max_age;
}

uint Creature::getMaxAge()
{
    return this -> max_age;
}

//**********************************************************
// HEALTH
//**********************************************************


void Creature::setHealth(uint health)
{
    this -> health = health;
}

uint Creature::getHealth()
{
    return this -> health;
}

void Creature::setMaxHealth(uint max_health)
{
    this -> max_health = max_health;
}

uint Creature::getMaxHealth()
{
    return this -> max_health;
}

//**********************************************************
// HUNGER
//**********************************************************


void Creature::setHunger(uint hunger)
{
    this -> hunger = hunger;
}

uint Creature::getHunger()
{
    return this -> hunger;
}

void Creature::setMaxHunger(uint max_hunger)
{
    this -> max_hunger = max_hunger;
}

uint Creature::getMaxHunger()
{
    return this -> max_hunger;
}

//**********************************************************
// ENDURANCE
//**********************************************************

void Creature::setEndurance(uint endurance)
{
    this -> endurance = endurance;
}

uint Creature::getEndurance()
{
    return this -> endurance;
}

void Creature::setMaxEndurance(uint max_endurance)
{
    this -> max_endurance = max_endurance;
}

uint Creature::getMaxEndurance()
{
    return this -> max_endurance;
}

//**********************************************************
// SLEEPINESS
//**********************************************************

void Creature::setSleepiness(uint max_sleepiness)
{
    this -> max_sleepiness = max_sleepiness;
}

uint Creature::getSleepiness()
{
    return this -> max_sleepiness;
}

void Creature::setMaxSleepiness(uint max_sleepiness)
{
    this -> max_sleepiness = max_sleepiness;
}

uint Creature::getMaxSleepiness()
{
    return this -> max_sleepiness;
}

//**********************************************************
// FORCE
//**********************************************************

void Creature::setForce(uint force)
{
    this -> force = force;
}

uint Creature::getForce()
{
    return this -> force;
}


const Object* Creature::getAim()
{
    return this -> aim;
}

//******************************************************************************
// CHANGING HEALTH.
//******************************************************************************

void Creature::decreaseHealth(uint delta)
{
    if(this -> health > delta)
    {
        this -> health -= delta;
    }
    else
    {
        this -> health = 0;
    }
}

void Creature::increaseHealth(uint delta)
{
    if(this -> health + delta < this -> max_health)
    {
        this -> health += delta;
    }
    else
    {
        this -> health = this -> max_health;
    }
}

void Creature::feed(uint delta)
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

// look for objects around and count danger level
void Creature::updateDanger()
{
    ObjectHeap::const_iterator iter;
    this -> danger = 0;

    // Only creatures and weather can be dangerous
    for(
        iter = objects_around.begin(CREATURE);
        iter != objects_around.end(CREATURE); iter++
       )
    {
        Creature* creat = dynamic_cast<Creature*>(*iter);
        if (this -> getDangerLevel() < creat -> getDangerLevel() + 10)
            this -> danger += creat -> getDangerLevel();
    }

    for(
        iter = objects_around.begin(WEATHER);
        iter != objects_around.end(WEATHER); iter++
       )
    {
        Weather* weath = dynamic_cast<Weather*>(*iter);
        if (this -> getDangerLevel() < weath -> getDangerLevel() + 10)
            this -> danger += weath -> getDangerLevel();
    }
}

void Creature:: chooseDirectionToEscape()
{
    // Initialize vector of escaping.
    double global_x = 0;
    double global_y = 0;

    // Add all dangerous objects danger levels as vectors
    // with length equal to object's danger level and
    // angle equal to direction to the object
    ObjectHeap::const_iterator iter;
    for(
        iter = objects_around.begin(CREATURE);
        iter != objects_around.end(CREATURE); iter++
       )
    {
        if (this -> getDangerLevel() < (*iter) -> getDangerLevel() + 10)
        {
            angle = getCoords().getAngle((*iter) -> getCoords());
            global_x += (*iter) -> getDangerLevel() * cos(angle);
            global_y += (*iter) -> getDangerLevel() * sin(angle);
        }
    }

    for(
        iter = objects_around.begin(WEATHER);
        iter != objects_around.end(WEATHER); iter++
       )
    {
        if (this -> getDangerLevel() < (*iter) -> getDangerLevel() + 10)
        {
            angle = getCoords().getAngle((*iter) -> getCoords());
            global_x += (*iter) -> getDangerLevel() * cos(this -> angle);
            global_y += (*iter) -> getDangerLevel() * sin(this -> angle);
        }
    }

    // go to the opposite direction of biggest danger
    this -> angle = atan(global_y / global_x) + M_PI;
    aim = 0;
    direction_is_set = true;
}

// Go with the given speed
void Creature::go(SpeedType speed)
{
    // If we could not move, then reset direction
    if (prev_action == GO && prev_action_state == FAILED)
        direction_is_set = false;

    // if we don't have any aim, go the way we went before
    if (!aim)
    {
        // if there is no direction, then go random
        // or there is an error in angle
        if (!direction_is_set || isnan(angle))
        {
            direction_is_set = true;
            angle = Random::double_num(M_PI * 2);
        }
    }
    else
    {
        // if we can't go the way we went, or the aim changed,
        // reset route
        if (!direction_is_set || aim != goal)
        {
            goal = aim;
            //generate route
            route = generateRoute();

            angle = this -> getCoords().getAngle(route.top()); 
            direction_is_set = true;
        }

        // if we reached the target, face to the next point
        if (this -> getShape().hitTest(route.top()))
        {
            route.pop();

            // check if we reached the end
            if (route.empty())
            {
                direction_is_set = false;
                return;
            }

            // face to the the next point
            angle = this -> getCoords().getAngle(route.top());
            direction_is_set = true;
        }
    }

    // Generate GO action
    Action act(GO, this);
    act.addParam<double>("angle", angle);
    act.addParam<SpeedType>("speed", speed);
    this -> actions.push_back(act);
}


//******************************************************************************
// INHERETED THINGS.
//******************************************************************************

void Creature::damage(uint delta)
{
    this -> decreaseHealth(delta);
}

void Creature::heal(uint delta)
{
    this -> increaseHealth(delta);
}

uint Creature::getHealthPoints() const
{
    return this -> health;
}

uint Creature::getMaxHealthPoints() const
{
    return this -> max_health;
}

std::string Creature::printObjectInfo() const
{
    std::string output = Object::printObjectInfo();

    std::stringstream ss;

    // TODO: Print current action. Need to print steps?
    ss << "Force\t\t\t"           << force << std::endl <<
          "Age\t\t\t"             << age << "/" << max_age << std::endl <<
          "Endurance\t\t"         << endurance << "/" << max_endurance <<
                                     std::endl <<
          "Sleepiness\t\t"        << sleepiness << "/" << max_sleepiness <<
                                     std::endl <<
          "Hunger\t\t\t"          << hunger << "/" << max_hunger << std::endl <<
          "Need in descendants\t" << need_in_descendants << std::endl <<
          "Danger around\t\t"     << danger << std::endl <<
          "Direction is set\t"    << (direction_is_set ? "yes" : "no") <<
                                     std::endl <<
          "Direction angle\t\t"   << angle << std::endl <<
          "Aim ID\t\t\t"          << (aim == nullptr ? "none" :
                                     std::to_string(aim -> getObjectID())) <<
                                     std::endl <<
          "Inventory\t\t\t"       << std::endl << inventory -> printIDs() <<
          "Objects around\t\t"    << std::endl << objects_around.printIDs();

    return output + ss.str();
}

double Creature::setDirection()
{
    if (aim)
        return this -> getCoords().getAngle(aim -> getCoords());
    else
        return Random::double_num(M_PI * 2);
}

//**********************************************************
// DEBUG
//**********************************************************

uint Creature::getCurrentDecision() const
{
    return current_decision;
}

//**********************************************************
// ACTIONS
//**********************************************************

void Creature::clearActions()
{
    // TODO
    // Make it better (more info, history)
    if (actions.size())
    {
        prev_action = actions[0].getType();
        prev_action_state = actions[0].getState();
        prev_action_error = actions[0].getError();
    }
    actions.clear();
}
