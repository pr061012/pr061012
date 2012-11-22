/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <iostream>
#include "../../model/Utilities/Vector/Vector.h"
#include <assert.h>
#include <cmath>

#define EPSILON 0.00000001

using namespace std;

int main()
{
    //**************************************************************************
    // TEST CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    Vector p1(2.5, 3);
    Vector p2(0, 4);

    // Getters tests
    assert(p1.getX() == 2.5 && p1.getY() == 3);
    assert(p2.getX() == 0   && p2.getY() == 4);

    // Operators +,-,!=
    assert(p1 + p2 == Vector(2.5, 7));
    assert(p1 - p2 == Vector(2.5, -1));
    assert(p1 != p2);

    // Setters
    p1.setX(4);
    p2.setY(0);

    assert(p1.getX() == 4 && p1.getY() == 3);
    assert(p2.getX() == 0   && p2.getY() == 0);

    // Distance
    assert(p1.getDistance(p2) == 5);

    // Distance between a line and a point
    Vector p3(4, 4);
    assert(fabs(p1.getDistanceToLine(p2, p3) - 1/sqrt(2)) < EPSILON);
    assert(fabs(p1.getDistanceToLine(p3, p2) -
                p1.getDistanceToLine(p2, p3)) < EPSILON);

    // Operators +=, -=, unary -
    p1 += Vector(10, 5) -= Vector(1, 13);

    assert(p1 == Vector(13, -5));
    assert(-p1 == Vector(-13, 5));

    //**********************************************************
    // Other utilities
    //**********************************************************
    
    p1 = Vector(0, 0);
    p2 = Vector(3, 3);
    p3 = Vector(0, 3);

    assert(p3.project(p1, p2) == Vector(1.5, 1.5));
    assert(Vector::scalarProduct(p2 - p3, p1 - p3) == 0);
    assert(Vector::scalarProduct(p2 - p1, p3 - p1) == 9);

    assert(fabs(p1.getAngle(p2) - M_PI/4) < EPSILON);
    assert(fabs(p1.getAngle(p3) - M_PI/2) < EPSILON);
    assert(fabs(p2.getAngle(p3)) < EPSILON);
    return 0;
}

