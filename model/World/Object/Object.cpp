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
}

Object::~Object()
{

}

//******************************************************************************
// DESTROYED FLAG.
//******************************************************************************

void Object::markAsDestroyed()
{
    this -> destroyed = true;
}

bool Object::isDestroyed()
{
    return this -> destroyed;
}

//******************************************************************************
// IMMORTALITY FLAG.
//******************************************************************************

void Object::makeMortal()
{
    this -> immortality = false;
}

void Object::makeImmortal()
{
    this -> immortality = true;
}

bool Object::isImmortal()
{
    return this -> immortality;
}

//******************************************************************************
// OBJECT TYPE.
//******************************************************************************

ObjectType Object::getType()
{
    return this -> type;
}

//******************************************************************************
// OBJECT SHAPE AND ANGLE.
//******************************************************************************

void Object::setShape(Shape new_var)
{
    this -> shape = new_var;
}

Shape Object::getShape()
{
    return this -> shape;
}

void Object::setAngle(double new_var)
{
    this -> angle = new_var;
}

double Object::getAngle()
{
    return this -> angle;
}
