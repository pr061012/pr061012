/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Object.h"


//**************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//**************************************************************************

Object::Object()
{
    initAttributes();
}

Object::~Object()
{

}

void Object::destroy()
{

}

void Object::initAttributes()
{
    this -> destroyed = false;
}

void Object::damage(int harm)
{
    this -> health -= harm;
}


//**************************************************************************
// ACCESSORS.
//**************************************************************************


void Object::setType(int new_var)
{
    this -> type = new_var;
}

int Object::getType()
{
    return this -> type;
}

void Object::setFrame(Frame new_var)
{
    this -> frame = new_var;
}


Frame Object::getFrame()
{
    return this -> frame;
}

void Object::setVisualState(VisualState new_var)
{
    this -> visual_state = new_var;
}

VisualState Object::getVisualState()
{
    return this -> visual_state;
}

void Object::setDestroyed(bool new_var)
{
    this -> destroyed = new_var;
}

bool Object::getDestroyed()
{
    return this -> destroyed;
}

void Object::setHealth(int new_var)
{
    this -> health = new_var;
}

int Object::getHealth()
{
    return this -> health;
}

void Object::setImmortal(bool new_var)
{
    this -> immortal = new_var;
}

bool Object::getImmortal()
{
    return this -> immortal;
}

void Object::setMaxHealth(int new_var)
{
    this -> max_health = new_var;
}

int Object::getMaxHealth()
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
