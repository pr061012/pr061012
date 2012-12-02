/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cmath>
#include <limits>

#include "Vector.h"
#include "../../../common/BasicDefines.h"
#include "../../../common/Math/DoubleComparison.h"

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

Vector Vector::project(const Vector& pt1, const Vector& pt2) const
{
    double length = pt1.getDistance(pt2);
    // if a line is not a line, project straight to the vector
    if (DoubleComparison::areEqual(length, 0))
    {
        return pt1;
    }
    // Triangle ABC: projecting C on AB
    // AB
    Vector vec_line = pt2 - pt1;
    // AC
    Vector vec_pt   = *this - pt1;
    // (AB, AC) = |AB|*|AC|*cos(AB^AC)
    // |AC'| = |AC|*cos(AB^AC)
    // scale * |AB| = |AC'| = (AC, AB) / |AB|
    double scale = scalarProduct(vec_pt, vec_line) / 
                   (pow(vec_line.getX(), 2) + pow(vec_line.getY(), 2));

    // OC' = OA + AC' = OA + AB * |AC'|/|AB|
    return pt1 + Vector(vec_line.getX() * scale, vec_line.getY() * scale); 
}

double Vector::scalarProduct(const Vector& vec1, const Vector& vec2)
{
    return vec1.getX() * vec2.getX() + vec1.getY() * vec2.getY();
}

double Vector::vectorProduct(const Vector& vec1, const Vector& vec2)
{
    return vec1.getX() * vec2.getY() - vec2.getX() * vec1.getY();
}

double Vector::getAngle(const Vector& vec) const
{
    return atan2((vec.getY() - y), (vec.getX() - x));
}

// Gets point's projection's parameter on the line,
// parametrized by points zero and one.
double Vector::getLineParameter(const Vector& zero, const Vector& one) const
{
    // pr_this = zero + (one - zero) * t
    // From Creature::project:
    // pr_this = zero + (one - zero) * (this - zero, one - zero) / |one - zero|
    // t = (this - zero, one - zero) / |one - zero|
    double dist = zero.getDistance(one);
    if (DoubleComparison::areEqual(dist, 0))
    {
        return 0;
    }
    return scalarProduct(*this - zero, one - zero) / dist;
}

// Finds the intersection of two lines defined with pairs of points.
Vector Vector::getLinesIntersection(const Vector& first_start, 
                                    const Vector& first_end,
                                    const Vector& second_start,
                                    const Vector& second_end)
{
    Vector v1 = first_end - first_start;
    Vector v2 = second_end - second_start;
    double a1 = v1.getY();
    double b1 = -v1.getX();
    double c1 = vectorProduct(first_end, first_start);
    double a2 = v2.getY();
    double b2 = -v2.getX();
    double c2 = vectorProduct(second_end, second_start);

    // Cramer's rule.
    Vector result;
    double det = a1 * b2 - a2 * b1;

    // No intersection or equal lines
    if (DoubleComparison::areEqual(det, 0))
    {
        result.setX(std::numeric_limits<double>::quiet_NaN());
        return result;
    }

    result.setX(c1 * b2 - c2 * b1);
    result.setY(a1 * c2 - c1 * a2);
    result /= det;
    return result;
}

//******************************************************************************
// COMPARING
//******************************************************************************

bool Vector::equals(const Vector& vector) const
{
    return  DoubleComparison::areEqual(x, vector.getX()) &&
            DoubleComparison::areEqual(y, vector.getY());
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

Vector Vector::operator*(double a) const
{
    return (Vector(x * a, y * a));
}

Vector Vector::operator/(double a) const
{
    return (Vector(x / a, y / a));
}

Vector& Vector::operator*=(double a)
{
    x *= a;
    y *= a;
    return *this;
}

Vector& Vector::operator/=(double a)
{
    x /= a;
    y /= a;
    return *this;
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
