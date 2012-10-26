/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <iostream>
#include "../../model/Utilities/Point/Point.h"
#include <assert.h>

using namespace std;

int main()
{
    //**************************************************************************
    // TEST CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    Point p1(2.5, 3);
    Point p2(0, 4);

    // Getters tests
    assert(p1.getX() == 2.5 && p1.getY() == 3);
    assert(p2.getX() == 0   && p2.getY() == 4);

    // Operators +,-,!=
    assert(p1 + p2 == Point(2.5, 7));
    assert(p1 - p2 == Point(2.5, -1));
    assert(p1 != p2);

    // Setters
    p1.setX(4);
    p2.setY(0);

    assert(p1.getX() == 4 && p1.getY() == 3);
    assert(p2.getX() == 0   && p2.getY() == 0);

    // Distance
    assert(p1.getDistance(p2) == 5);

    // Operators +=, -=, unary -
    p1 += Point(10, 5) -= Point(1, 13);

    assert(p1 == Point(13, -5));
    assert(-p1 == Point(-13, 5));

    return 0;
}

