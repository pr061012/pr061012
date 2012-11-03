/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Object.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Object::Object(ObjectType type) :
    type(type)
{
    this -> destroyed = false;
    this -> immortality = false;

    this -> angle = 0;

    this -> health = 0;
    this -> max_health = 0;
}

Object::~Object()
{

}

//******************************************************************************
// OBJECT'S LIFE.
//******************************************************************************

void Object::destroy()
{
    this -> destroyed = true;
}

void Object::decreaseHealth(unsigned int delta)
{
    if(!immortality)
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

//******************************************************************************
// ACCESSORS.
//******************************************************************************

ObjectType Object::getType()
{
    return this -> type;
}

void Object::setShape(Shape new_var)
{
    this -> shape = new_var;
}

Shape Object::getShape()
{
    return this -> shape;
}

void Object::setDestroyed(bool new_var)
{
    this -> destroyed = new_var;
}

bool Object::getDestroyed()
{
    return this -> destroyed;
}

void Object::setHealth(unsigned int new_var)
{
    this -> health = new_var;
}

unsigned int Object::getHealth()
{
    return this -> health;
}

void Object::setImmortality(bool new_var)
{
    this -> immortality = new_var;
}

bool Object::getImmortality()
{
    return this -> immortality;
}

void Object::setMaxHealth(unsigned int new_var)
{
    this -> max_health = new_var;
}

unsigned int Object::getMaxHealth()
{
    return this -> max_health;
}

void Object::setAngle(double new_var)
{
    this -> angle = new_var;
}

double Object::getAngle()
{
    return this -> angle;
}
