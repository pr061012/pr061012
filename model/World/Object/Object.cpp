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

void Object::setImmortality(bool new_var)
{
    this -> immortality = new_var;
}

bool Object::getImmortality()
{
    return this -> immortality;
}

void Object::setAngle(double new_var)
{
    this -> angle = new_var;
}

double Object::getAngle()
{
    return this -> angle;
}
