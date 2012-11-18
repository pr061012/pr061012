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
    safety      = 0; // we need in function to calculate it
                     // different for HUM and NON_HUM?
    // Initialize some inhereted things.
    setMaxHealth(health);
    setHealth(health);

}

Creature::~Creature()
{
    delete inventory;
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************
CreatureType Creature::getSubtype()
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

void Creature::updateSafety()
{
    ObjectHeap::const_iterator iter;
    this -> safety = 0;
    for(
        iter = objects_around.begin(CREATURE);
        iter != objects_around.end(CREATURE); iter++
       )
    {
        Creature* creat = dynamic_cast<Creature*>(*iter);
        if (this -> getDangerLevel() < creat -> getDangerLevel() + 10)
            this -> safety += creat -> getDangerLevel();
    }
    for(
        iter = objects_around.begin(WEATHER);
        iter != objects_around.end(WEATHER); iter++
       )
    {
        Weather* weath = dynamic_cast<Weather*>(*iter);
        if (this -> getDangerLevel() < weath -> getDangerLevel() + 10)
            this -> safety += weath -> getDangerLevel();
    }
}

void Creature:: chooseDirectionToEscape()
{
    double global_x = 0;
    double global_y = 0;
    ObjectHeap::const_iterator iter;
    for(
        iter = objects_around.begin(CREATURE);
        iter != objects_around.end(CREATURE); iter++
       )
    {
        Creature* creat = dynamic_cast<Creature*>(*iter);
        if (this -> getDangerLevel() < creat -> getDangerLevel() + 10)
        {
            this -> aim = creat;
            setDirection();
            global_x += creat -> getDangerLevel() * cos(this -> angle);
            global_y += creat -> getDangerLevel() * sin(this -> angle);
        }
    }
    for(
        iter = objects_around.begin(WEATHER);
        iter != objects_around.end(WEATHER); iter++
       )
    {
        Weather* weath = dynamic_cast<Weather*>(*iter);
        if (this -> getDangerLevel() < weath -> getDangerLevel() + 10)
        {
            this -> aim = weath;
            setDirection();
            global_x += weath -> getDangerLevel() * cos(this -> angle);
            global_y += weath -> getDangerLevel() * sin(this -> angle);
        }
    }
    this -> angle = atan(global_x / global_y) + M_PI;
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
