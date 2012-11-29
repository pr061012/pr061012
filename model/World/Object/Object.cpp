/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <sstream>

#include "../../../common/BasicDefines.h"

#include "Object.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

uint Object::CURRENT_ID = 0;

Object::Object(ObjectType type, bool solidity, bool immortality) :
    id(CURRENT_ID++),
    type(type),
    shape(Shape(Vector(0, 0), SHP_DEFAULT, SZ_DEFAULT)),
    destroyed(false),
    immortality(immortality),
    solidity(solidity),
    angle(0),
    danger_level(0),
    weight(0)
{
}

Object::~Object()
{
}


//******************************************************************************
// OBJECT'S INFORMATION.
//******************************************************************************

std::string Object::printObjectInfo() const
{
    std::stringstream ss;

    ss << "ID\t\t\t"             << id << std::endl <<
          "Type\t\t\t"           << getTypeName() << std::endl <<
          "Flags\t\t\t"          << (destroyed   ? "d" : "") <<
                                    (immortality ? "i" : "") <<
                                    (solidity    ? "s" : "") << std::endl <<
          "Centre coordinates\t" << "(" << shape.getCenter().getX() << ", " <<
                                           shape.getCenter().getY() << ")" <<
                                    std::endl <<
          "HP\t\t\t"             << getHealthPoints() << "/" <<
                                    getMaxHealthPoints() << std::endl <<
          "Danger level\t\t"     << danger_level << std::endl <<
          "Weight\t\t\t"         << weight << std::endl <<
          "Shape\t\t\t"          << shape.getTypeName() << " (" <<
                                    shape.getSize() << ")" << std::endl;

    return ss.str();
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
// SOLIDITY.
//******************************************************************************

void Object::makeSolid()
{
    this -> solidity = true;
}

void Object::makeNonSolid()
{
    this -> solidity = false;
}

bool Object::isSolid() const
{
    return this -> solidity;
}

//******************************************************************************
// DANGER.
//******************************************************************************

uint Object::getDangerLevel() const
{
    return this -> danger_level;
}

void Object::setDangerLevel(uint danger_level)
{
    this -> danger_level = danger_level;
}

//******************************************************************************
// WEIGHT.
//******************************************************************************

uint Object::getWeight() const
{
    return this -> weight;
}

void Object::setWeight(uint weight)
{
    this -> weight = weight;
}

//******************************************************************************
// OBJECT TYPE AND ID.
//******************************************************************************

ObjectType Object::getType() const
{
    return this -> type;
}

uint Object::getObjectID() const
{
    return this -> id;
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

void Object::setCoords(const Vector& coords)
{
    shape.setCenter(coords);
}

const Vector& Object::getCoords() const
{
    return shape.getCenter();
}

//******************************************************************************
// CAST OPERATORS.
//******************************************************************************

Object::operator const ViewObject()
{
    Vector v = this -> getShape().getCenter();
    return ViewObject(this -> getType(), v.getX(), v.getY());
}
