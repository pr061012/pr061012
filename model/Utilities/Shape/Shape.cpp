/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Shape.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Shape::Shape (Point center, int type, double size )
{
    this -> type = (ShapeType) type;
    this -> center = center;
    this -> size = size;
    this -> last_center = center;
    switch(type)
    {
        case CIRCLE:
            left_bottom = Point(-size, -size);
            right_top = -left_bottom;
            break;
        case SQUARE:
            left_bottom = Point(-size/2, -size/2);
            right_top = - left_bottom;
            break;
    }
}

Shape::~Shape ()
{
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void Shape::setCenter ( Point new_var )
{
    last_center = center;
    center = new_var;
}

Point Shape::getCenter ( )
{
    return center;
}

void Shape::setType(int type)
{
    this -> type = (ShapeType) type;
}

int Shape::getType()
{
    return type;
}

void Shape::setSize(double size)
{
    this -> size = size;
}

double Shape::getSize()
{
    return size;
}

//******************************************************************************
// HIT-TEST METHODS.
//******************************************************************************

Point Shape::getLeftBottom()
{
    return center + left_bottom;
}

Point Shape::getRightTop()
{
    return center + right_top;
}

Point Shape::getLastCenter()
{
    return last_center;
}

// blank implementations of hittset
bool hitTest (Point point)
{
    return false;
}

bool hitTest (Shape shape)
{
    return false;
}

// Calculates intersections
int Shape::intersect(Shape shape)
{
    // copy data
    Point this_lb = this -> getLeftBottom();
    Point this_rt = this -> getRightTop();
    Point shape_lb = this -> getLeftBottom();
    Point shape_rt = this -> getRightTop();

    double x1 = this_lb.getX();
    double y1 = this_lb.getY();
    double x2 = this_lb.getX();
    double y2 = this_lb.getY();
    double x3 = shape_lb.getX();
    double y3 = shape_lb.getY();
    double x4 = shape_rt.getX();
    double y4 = shape_rt.getY();

    // check if MBB don't intersect
    if (x4 < x1 || x3 >= x2 || y4 < y1 || y4 >= y2)
        return NO_INTERSECTION;

    int result = 0;

    // check if there is a part of another shape to the left
    if (x3 < x1 && x4 > x1)
        result &= LEFT;

    // to the right
    if (x3 <= x2 && x4 >= x2)
        result &= RIGHT;

    // to the bottom
    if (y3 < y1 && y4 > y1)
        result &= BOTTOM;

    if (y3 <= y2 && y4 >= y2)
        result &= UP;

    return result;
}



