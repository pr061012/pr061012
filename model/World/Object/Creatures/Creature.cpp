/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Creature.h"
#include "../../../BasicDefines.h"
#include "../../../../common/Random/Random.h"


//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Creature::Creature(CreatureType type, const DecisionMaker & dmaker) :
    Object(CREATURE),
    subtype(type),
    inventory(new ObjectHeap),
    objects_around(new ObjectHeap),
    brains(dmaker)
{
    attrs = arma::mat(ATR_CONST, 1);
    // Randomly initialize some values.
    max_hunger      = Random::int_range(CREAT_HUNGER_MIN,     CREAT_HUNGER_MAX);
    max_sleepiness  = Random::int_range(CREAT_SLEEPINESS_MIN, CREAT_SLEEPINESS_MAX);
    int health      = Random::int_range(CREAT_HEALTH_MIN,     CREAT_HEALTH_MAX);

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
    delete objects_around;
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void Creature::setWindow(ObjectHeap * window)
{
    this -> window = window;
}

ObjectHeap * Creature::getWindow()
{
    return this -> window;
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
