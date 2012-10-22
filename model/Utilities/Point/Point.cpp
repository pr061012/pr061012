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
