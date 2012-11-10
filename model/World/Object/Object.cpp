/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "../../BasicDefines.h"

#include "Object.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Object::Object(ObjectType type, double x, double y) :
    type(type),
    shape(Shape(Point(x, y), SHP_DEFAULT, SZ_DEFAULT))
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

bool Object::isDestroyed() const
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

bool Object::isImmortal() const
{
    return this -> immortality;
}

//******************************************************************************
// OBJECT TYPE.
//******************************************************************************

ObjectType Object::getType() const
{
    return this -> type;
}

//******************************************************************************
// OBJECT SHAPE AND ANGLE.
//******************************************************************************

void Object::setShapeType(ShapeType type)
{
    this -> shape.setType(type);
}

void Object::setShapeSize(double size)
{
    this -> shape.setSize(size);
}

Shape Object::getShape() const
{
    return this -> shape;
}

void Object::setAngle(double new_var)
{
    this -> angle = new_var;
}

double Object::getAngle() const
{
    return this -> angle;
}

void Object::setCoords(const Point& coords)
{
    shape.setCenter(coords);
}

const Point& Object::getCoords() const
{
    return shape.getCenter();
}
