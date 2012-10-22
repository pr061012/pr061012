#include "Point.h"
#include <cmath>

// Constructors/Destructors
//  

Point::Point (double x, double y )
{
    this -> x = x;
    this -> y = y;
}

Point::~Point ( ) { }

//  
// Methods
//  

// Operators
//
Point Point::operator + (Point point)
{
    return Point(point.getX() + x, point.getY() + y);
}

Point Point::operator - (Point point)
{
    return Point(x - point.getX(), y - point.getY());
}

Point& Point::operator -= (Point point)
{
    x -= point.getX();
    y -= point.getY();
    return *this;
}

Point& Point::operator += (Point point)
{
    x += point.getX();
    y += point.getY();
    return *this;
}

bool Point::operator == (Point point)
{
    return this -> equals(point);
}

bool Point::operator != (Point point)
{
    return !(this -> equals(point));
}

// Accessor methods
//  
double Point::getX()
{
    return x;
}

double Point::getY()
{
    return y;
}

void Point::setX(double x)
{
    this -> x = x;
}

void Point::setY(double y)
{
    this -> y = y;
}

// Other methods
//
double Point::getDistance(Point point)
{
    return sqrt(pow(x - point.getX(), 2) + pow (y - point.getY(), 2));
}

bool Point::equals(Point point)
{
    return (x == point.getX()) && (y == point.getY());
}
