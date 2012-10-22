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


