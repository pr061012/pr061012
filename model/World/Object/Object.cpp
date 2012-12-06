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

Object::Object(ObjectType type, bool solidity, bool movable, bool flyable,
               bool pickable, bool immortality) :
    id(CURRENT_ID++),
    type(type),
    shape(Shape(Vector(0, 0), SHP_DEFAULT, SZ_DEFAULT)),
    angle(0),
    danger_level(0),
    weight(0),
    normal_speed(0),
    destroyed(false),
    immortality(immortality),
    solidity(solidity),
    pickable(pickable),
    movable(movable),
    flyable(flyable),
    is_currently_flying(false)
{
}

Object::~Object()
{
}


//******************************************************************************
// OBJECT'S INFORMATION.
//******************************************************************************

std::string Object::printObjectInfo(bool full) const
{
    std::stringstream ss;

    // Printing information.
    ss << "#" << id << " (" << getTypeName() << ")" << std::endl <<

          // Common flags.
          (destroyed   ? "Destroyed\n" : "") <<
          (immortality ? "Immortal\n"  : "") <<
          (solidity    ? "Solid\n"     : "") <<
          (movable     ? "Movable\n"   : "") <<
          (pickable    ? "Pickable\n"  : "") <<
          (flyable     ? "Flyable"     : "") <<
          (flyable && isCurrentlyFlying() ? " (currently flying)\n" : "\n") <<

          // Coordinates.
          insertSpaces("Center")       << "("  << shape.getCenter().getX() <<
                                          ", " << shape.getCenter().getY() <<
                                          ")" << std::endl <<
          // Health points.
          insertSpaces("HP")           << getHealthPoints() << "/" <<
                                          getMaxHealthPoints() << std::endl <<
          // Danger level and weight.
          insertSpaces("Danger level") << danger_level << std::endl <<
          insertSpaces("Weight")       << weight << std::endl;

    // Information only for full-mode.
    if (full)
    {
        ss << insertSpaces("Speed") << normal_speed << std::endl <<
              insertSpaces("Shape") << shape.getTypeName() << " (" <<
                                       shape.getSize() << ")" << std::endl;
    }

    return ss.str();
}

std::string Object::insertSpaces(std::string str, uint indent) const
{
    return str + std::string(indent - str.size(), ' ');
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
// PICKABILITY.
//******************************************************************************

void Object::makePickable()
{
    this -> pickable = true;
}

void Object::makeNonPickable()
{
    this -> pickable = false;
}

bool Object::isPickable() const
{
    return this -> pickable;
}

//******************************************************************************
// MOVABILITY.
//******************************************************************************

void Object::makeMovable()
{
    this -> movable = true;
}

void Object::makeImmovable()
{
    this -> movable = false;
}

bool Object::isMovable() const
{
    return this -> movable;
}

//******************************************************************************
// ABILITY TO FLY.
//******************************************************************************

void Object::makeFlyable()
{
    this -> flyable = true;
}

void Object::makeNonFlyable()
{
    this -> flyable = false;
}

bool Object::isFlyable() const
{
    return this -> flyable;
}

//******************************************************************************
// FLYING FLAG.
//******************************************************************************

void Object::makeFlying()
{
    this -> is_currently_flying = true;
}

void Object::makeNonFlying()
{
    this -> is_currently_flying = false;
}

bool Object::isCurrentlyFlying() const
{
    return this -> is_currently_flying;
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
// NORMAL SPEED.
//******************************************************************************

double Object::getNormalSpeed() const
{
    return this -> normal_speed;
}

void Object::setNormalSpeed(double speed)
{
    this -> normal_speed = speed;
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
