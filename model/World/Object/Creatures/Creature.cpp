/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Creature.h"
#include "../../../BasicFuncs.h"
#include "../../../BasicDefines.h"


//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Creature::Creature(CreatureType type, const DecisionMaker & dmaker) :
    Object(CREATURE),
    subtype(type),
    inventory(new ObjectHeap),
    brains(dmaker)

{
    attrs = arma::mat(ATR_CONST, 1);
    // Randomly initialize some values.
    max_hunger      = randFromRange(CREAT_HUNGER_MIN,     CREAT_HUNGER_MAX);
    max_sleepiness  = randFromRange(CREAT_SLEEPINESS_MIN, CREAT_SLEEPINESS_MAX);
    int health      = randFromRange(CREAT_HEALTH_MIN,     CREAT_HEALTH_MAX);

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

void Creature::setWindow(const ObjectHeap * window)
{
    this -> window = window;
}

const ObjectHeap * Creature::getWindow()
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

void Creature::setAge(unsigned int age)
{
    this -> age = age;
}

unsigned int Creature::getAge()
{
    return this -> age;
}

void Creature::setMaxAge(unsigned int max_age)
{
    this -> max_age = max_age;
}

unsigned int Creature::getMaxAge()
{
    return this -> max_age;
}


void Creature::setHealth(unsigned int health)
{
    this -> health = health;
}

unsigned int Creature::getHealth()
{
    return this -> health;
}

void Creature::setMaxHealth(unsigned int max_health)
{
    this -> max_health = max_health;
}

unsigned int Creature::getMaxHealth()
{
    return this -> max_health;
}

//******************************************************************************
// OBJECT'S LIFE.
//******************************************************************************

void Creature::decreaseHealth(unsigned int delta)
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

void Creature::increaseHealth(unsigned int delta)
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


