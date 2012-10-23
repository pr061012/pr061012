/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Point.h"
#include <cmath>

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Point::Point(double x, double y)
{
    this -> x = x;
    this -> y = y;
}

Point::Point()
{
    this -> x = 0;
    this -> y = 0;
}

Point::~Point()
{

}

//******************************************************************************
// DISTANCE.
//******************************************************************************

double Point::getDistance(Point point)
{
    return sqrt(pow(this -> x - point.getX(), 2) + pow (this -> y - point.getY(), 2));
}

bool Point::equals(Point point)
{
    return (x == point.getX()) && (y == point.getY());
}

//******************************************************************************
// OPERATORS.
//******************************************************************************

Point Point::operator+(Point point)
{
    return Point(point.getX() + x, point.getY() + y);
}

Point Point::operator-(Point point)
{
    return Point(x - point.getX(), y - point.getY());
}

Point& Point::operator-=(Point point)
{
    x -= point.getX();
    y -= point.getY();
    return *this;
}

Point& Point::operator+=(Point point)
{
    x += point.getX();
    y += point.getY();
    return *this;
}

bool Point::operator==(Point point)
{
    return this -> equals(point);
}

bool Point::operator!=(Point point)
{
    return !(this -> equals(point));
}

Point Point::operator -()
{
    return (Point(-x, -y));
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

double Point::getX()
{
    return this -> x;
}

double Point::getY()
{
    return this -> y;
}

void Point::setX(double x)
{
    this -> x = x;
}

void Point::setY(double y)
{
    this -> y = y;
}
