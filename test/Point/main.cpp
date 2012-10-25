#include <iostream>
#include "../../model/Utilities/Point/Point.h"
#include <assert.h>

using namespace std;

int main()
{
    Point p1(2.5, 3);
    Point p2(0, 4);
    assert(p1.getX() == 2.5 && p1.getY() == 3);
    assert(p2.getX() == 0   && p2.getY() == 4);
    assert(p1 + p2 == Point(2.5, 7));
    assert(p1 - p2 == Point(2.5, -1));
    assert(p1 != p2);
    p1.setX(4);
    p2.setY(0);
    assert(p1.getX() == 4 && p1.getY() == 3);
    assert(p2.getX() == 0   && p2.getY() == 0);
    assert(p1.getDistance(p2) == 5);
    p1 += Point(10, 5) -= Point(1, 13);
    assert(p1 == Point(13, -5));
    assert(-p1 == Point(-13, 5));
    cout << "Hello World!" << endl;
    return 0;
}

