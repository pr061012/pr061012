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

int Shape::intersect(Shape Shape)
{
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

    int result = 0;

    return result;
}



