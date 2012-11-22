/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cmath>

#include "Creature.h"
#include "../../../../common/BasicDefines.h"
#include "../../../../common/Random/Random.h"
#include "../Weather/Weather.h"


//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Creature::Creature(CreatureType type, const DecisionMaker & dmaker) :
    Object(CREATURE),
    subtype(type),
    inventory(new ObjectHeap),
    brains(dmaker)
{
    attrs = arma::mat(DM_ATR_CONST, 1);
    // Randomly initialize some values.
    max_hunger      = Random::int_range(CREAT_HUNGER_MIN,     CREAT_HUNGER_MAX);
    max_sleepiness  = Random::int_range(CREAT_SLEEPINESS_MIN, CREAT_SLEEPINESS_MAX);
    max_endurance   = Random::int_range(CREAT_ENDURANCE_MAX,  CREAT_ENDURANCE_MAX);
    int health      = Random::int_range(CREAT_HEALTH_MIN,     CREAT_HEALTH_MAX);
    force           = Random::int_range(CREAT_FORCE_MIN,      CREAT_FORCE_MAX);

    // Initialize other values.
    hunger      = 100 - max_hunger;
    sleepiness  = 100 - max_sleepiness;
    danger      = 0; // we need in function to calculate it
                     // different for HUM and NON_HUM?
    endurance   = max_endurance;
    // Initialize some inhereted things.
    setMaxHealth(health);
    setHealth(health);
    
    // Init vars for moving
    goal = 0;
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

ObjectHeap * Creature::getInventory()
{
    return this -> inventory;
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
}

// Go with the given speed
void Creature::go(SpeedType speed)
{
    bool failed = false;

    // First check if previous go action failed
    for (std::vector<Action>::iterator i = actions.begin();
            i != actions.end(); i++)
    {
        if ((*i).isFailed())
        {
            failed = true;
        }
    }

    // If we could not move, then reset direction
    if (failed)
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
            route = generateRoute(goal);

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

// TODO
// Implement A*
Creature::Path Creature::generateRoute(Object * goal)
{
    // Find 
    double miny = this -> getCoords().getY();
    double minx = this -> getCoords().getX();
    double maxx = minx;
    double maxy = miny;

    Path result;
    result.push(goal -> getCoords());
    return result;
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

double Creature::setDirection()
{
    double delta_x = aim -> getCoords().getX() - this -> getCoords().getX();
    double delta_y = aim -> getCoords().getY() - this -> getCoords().getY();
    return angle = atan(delta_x / delta_y);
}

//**********************************************************
// DEBUG
//**********************************************************

uint Creature::getCurrentDecision() const
{
    return current_decision;
}
