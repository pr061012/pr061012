/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Creature.h"

//******************************************************************************
// STATIC FUNCTIONS.
//******************************************************************************

static inline int randFromRange(int low_boundary, int top_boundary)
{
    return rand() % (top_boundary - low_boundary) + low_boundary + 1;
}


//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Creature::Creature(CreatureType type, const DecisionMaker & dmaker) :
    Object(CREATURE),
    subtype(type),
    brains(dmaker),
    inventory(new ObjectHeap)
{
	// Randomly initialize some values.
    max_hunger      = randFromRange(HUNGER_MIN,     HUNGER_MAX);
    max_sleepiness  = randFromRange(SLEEPINESS_MIN, SLEEPINESS_MAX);
	int health = randFromRange(NHUM_HEALTH_MIN, NHUM_HEALTH_MAX);

    // Initialize other values.
	hunger      = 100 - max_hunger;
    sleepiness  = 100 - max_sleepiness;
	safety		= 0; //we need in function to calculate it
					 //different for HUM and NON_HUM?
	// Initialize some inhereted things.
	setMaxHealth(health);
    setHealth(100 - health);
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

void Object::decreaseHealth(unsigned int delta)
{
	if(this -> health > delta)
	{
		this -> health -= delta;
	}
	else
	{
		this -> health = 0;
		destroy();
	}
}

void Object::increaseHealth(unsigned int delta)
{
    if(this -> health + delta < this->max_health)
    {
        this -> health += delta;
    }
    else
    {
        this -> health = this -> max_health;
    }
}

