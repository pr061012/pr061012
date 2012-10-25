#include <iostream>
#include "../../model/Utilities/Shape/Shape.h"
#include <assert.h>

using namespace std;

int main()
{
    Shape sh1(Point(1, 1), SQUARE, 10);
    Shape sh2(Point(-5, -7.5), CIRCLE, 12);

    //Accessors tests
    //
    //Getters
    //
    assert((sh1.getSize() == 10) && (sh2.getSize() == 12));
    assert(sh1.getCenter() + sh2.getCenter() == Point(-4, -6.5));
    assert(sh1.getType() == SQUARE && sh2.getType() == CIRCLE);

    //Setters
    //
    sh1.setCenter(Point(15, -3.14));
    sh2.setCenter(Point(2.71, 0));
    sh1.setSize(20);
    sh2.setType(SQUARE);
    sh1.setType(CIRCLE);

    assert(sh1.getSize() == 20);
    assert(sh1.getCenter() + sh2.getCenter() == Point(17.71, -3.14));
    assert(sh1.getType() == CIRCLE && sh2.getType() == SQUARE);

    cout << "Hello World!" << endl;
    return 0;
}

