/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Point.h"
#include <cmath>

#define EPSILON 0.00000001

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

double Point::getDistance(const Point& point) const
{
    return sqrt(pow(this -> x - point.getX(), 2) +
                pow(this -> y - point.getY(), 2));
}

// get distance to line using vector product
double Point::getDistanceToLine(const Point& line_start,
                                const Point& line_end) const
{
    Point a = *this - line_start;
    Point b = line_end - line_start;
    return fabs(a.getX() * b.getY() - a.getY() * b.getX()) /
            line_start.getDistance(line_end);
}

//******************************************************************************
// COMPARING
//******************************************************************************

bool Point::equals(const Point& point) const
{
    return  (fabs(x - point.getX()) < EPSILON) &&
            (fabs(y - point.getY()) < EPSILON);
}

//******************************************************************************
// OPERATORS.
//******************************************************************************

Point Point::operator+(Point point) const
{
    return Point(point.getX() + x, point.getY() + y);
}

Point Point::operator-(Point point) const
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

bool Point::operator==(Point point) const
{
    return this -> equals(point);
}

bool Point::operator!=(Point point) const
{
    return !(this -> equals(point));
}

Point Point::operator -() const
{
    return (Point(-x, -y));
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

double Point::getX() const
{
    return this -> x;
}

double Point::getY() const
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
