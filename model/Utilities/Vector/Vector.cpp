/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cmath>

#include "Vector.h"
#include "../../../common/BasicDefines.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Vector::Vector(double x, double y)
{
    this -> x = x;
    this -> y = y;
}

Vector::Vector()
{
    this -> x = 0;
    this -> y = 0;
}

Vector::~Vector()
{

}

//******************************************************************************
// DISTANCE.
//******************************************************************************

double Vector::getDistance(Vector vector) const
{
    return sqrt(pow(this -> x - vector.getX(), 2) +
                pow(this -> y - vector.getY(), 2));
}

// get distance to line using vector product
double Vector::getDistanceToLine(const Vector& line_start,
                                const Vector& line_end) const
{
    Vector a = *this - line_start;
    Vector b = line_end - line_start;
    return fabs(a.getX() * b.getY() - a.getY() * b.getX()) /
            line_start.getDistance(line_end);
}

//**********************************************************
// OTHER UTILITIES
//**********************************************************

Vector Vector::project(Vector pt1, Vector pt2) const
{
    double length = pt1.getDistance(pt2);
    // if a line is not a line, project straight to the vector
    if (fabs(length) < MATH_EPSILON)
    {
        return pt1;
    }

    Vector vec_line = pt2 - pt1;
    Vector vec_pt   = *this - pt1;
    double scale = scalarProduct(vec_pt, vec_line) / 
                   (pow(vec_line.getX(), 2) + pow(vec_line.getY(), 2));
    return pt1 + Vector(vec_line.getX() * scale, vec_line.getY() * scale); 
}

double Vector::scalarProduct(Vector vec1, Vector vec2)
{
    return vec1.getX() * vec2.getX() + vec1.getY() * vec2.getY();
}

//******************************************************************************
// COMPARING
//******************************************************************************

bool Vector::equals(const Vector& vector) const
{
    return  (fabs(x - vector.getX()) < MATH_EPSILON) &&
            (fabs(y - vector.getY()) < MATH_EPSILON);
}

//******************************************************************************
// OPERATORS.
//******************************************************************************

Vector Vector::operator+(Vector vector) const
{
    return Vector(vector.getX() + x, vector.getY() + y);
}

Vector Vector::operator-(Vector vector) const
{
    return Vector(x - vector.getX(), y - vector.getY());
}

Vector& Vector::operator-=(Vector vector)
{
    x -= vector.getX();
    y -= vector.getY();
    return *this;
}

Vector& Vector::operator+=(Vector vector)
{
    x += vector.getX();
    y += vector.getY();
    return *this;
}

bool Vector::operator==(Vector vector) const
{
    return this -> equals(vector);
}

bool Vector::operator!=(Vector vector) const
{
    return !(this -> equals(vector));
}

Vector Vector::operator -() const
{
    return (Vector(-x, -y));
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

double Vector::getX() const
{
    return this -> x;
}

double Vector::getY() const
{
    return this -> y;
}

void Vector::setX(double x)
{
    this -> x = x;
}

void Vector::setY(double y)
{
    this -> y = y;
}
