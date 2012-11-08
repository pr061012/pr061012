/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Shape.h"
#include <cmath>

#include <iostream>

#define EPSILON 0.00000001

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Shape::Shape (Point center, int type, double size )
{
    this -> type = (ShapeType) type;
    this -> center = center;
    this -> size = size;
    this -> last_center = center;
    this -> computeCorners();
}

Shape::Shape()
{
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

const Point& Shape::getCenter ( ) const
{
    return center;
}

void Shape::setType(int type)
{
    this -> type = (ShapeType) type;
}

int Shape::getType() const
{
    return type;
}

void Shape::setSize(double size)
{
    this -> size = size;
    this -> computeCorners();

}

double Shape::getSize() const
{
    return size;
}

//******************************************************************************
// CORNER METHODS
//******************************************************************************

void Shape::computeCorners()
{
    switch(type)
    {
        case CIRCLE: case SQUARE:
            left_bottom = Point(-size/2, -size/2);
            right_top = -left_bottom;
            break;
    }
}

Point Shape::getLeftBottom() const
{
    return center + left_bottom;
}

Point Shape::getRightTop() const
{
    return center + right_top;
}

Point Shape::getLastCenter()
{
    return last_center;
}

//******************************************************************************
// HIT-TEST METHODS.
//******************************************************************************

// checks hittest with a point
bool Shape::hitTest (const Point& point) const
{
    switch(type)
    {
        case CIRCLE:
            // if a distance between a point and a circle center is less than
            // radius, return true
            if (center.getDistance(point) - size/2 <= EPSILON)
            {
                return true;
            }
            break;

        case SQUARE:
            // if a point lies nearer than sides of a square, return true
            if (fabs(center.getY() - point.getY()) - size/2 <= EPSILON &&
                fabs(center.getX() - point.getX()) - size/2 <= EPSILON)
            {
                return true;
            }
            break;
    }
    return false;
}

// check hittest with another shape
bool Shape::hitTest (const Shape& shape) const
{
    std::cout << center.getDistance(shape.getCenter()) - size + shape.getSize()/ 2 << std::endl;
    switch(type)
    {
        case CIRCLE:
            switch(shape.getType())
            {
                // if sum of radiuses is more than distance between centers,
                // return true
                case CIRCLE:
                    if (center.getDistance(shape.getCenter()) <
                        (size + shape.getSize())/ 2)
                    {
                        return true;
                    }

                case SQUARE:
                    return squareCircleHitTest(shape, *this);
                    break;
            }
            break;

        case SQUARE:
            switch(shape.getType())
            {
                case CIRCLE:
                    return squareCircleHitTest(*this, shape);
                    break;

                // if a corner of one square lies inside another square,
                // return true (this way won't work for abstract rectangles)
                case SQUARE:
                    Point lb = getLeftBottom();
                    if (shape.hitTest(lb))
                    {
                        return true;
                    }

                    Point rt = getRightTop();
                    if (shape.hitTest(rt))
                    {
                        return true;
                    }

                    Point lt = (Point(lb.getX(), rt.getY()));
                    Point rb = Point(rt.getX(), lb.getY());

                    if (shape.hitTest(lt) ||
                        shape.hitTest(rb))
                    {
                        return true;
                    }

                    lb = shape.getLeftBottom();
                    if (this -> hitTest(lb))
                    {
                        return true;
                    }

                    rt = shape.getRightTop();
                    if (this -> hitTest(rt))
                    {
                        return true;
                    }

                    lt = (Point(lb.getX(), rt.getY()));
                    rb = Point(rt.getX(), lb.getY());

                    if (this -> hitTest(lt) ||
                        this -> hitTest(rb))
                    {
                        return true;
                    }
                    break;
            }
            break;
    }
    return false;
}

// hittest of square and circle
bool Shape::squareCircleHitTest(const Shape& square, const Shape& circle) const
{
    Point lb = square.getLeftBottom();
    Point rt = square.getRightTop();
    Point lt = Point(lb.getX(), rt.getY());
    Point rb = Point(rt.getX(), lb.getY());

    const Point &cs = circle.getCenter();
    double radius = circle.getSize() / 2;

    // if a corner is closer to a circle's center than radius length,
    // return true
    if (cs.getDistance(lb) <= radius || cs.getDistance(rt) <= radius ||
        cs.getDistance(lt) <= radius || cs.getDistance(rb) <= radius)
    {
        return true;
    }

    // a circle can intersect a square on its side but only if a circle's 
    // center x or y lies between corners x ,y
    double csx = cs.getX();
    double csy = cs.getY();

    if ((lb.getX() <= csx && rt.getX() >= csx &&
         (cs.getDistanceToLine(lt, rt) <= radius ||
          cs.getDistanceToLine(lb, rb) <= radius)) ||
        (lb.getY() <= csy && rt.getY() >= csy &&
         (cs.getDistanceToLine(lb, lt) <= radius ||
          cs.getDistanceToLine(rb, rt) <= radius)))
    {
        return true;
    }

    return false;
}

// Calculates intersections
int Shape::intersect(const Shape& shape)
{
    // copy data
    Point this_lb = this -> getLeftBottom();
    Point this_rt = this -> getRightTop();
    Point shape_lb = shape.getLeftBottom();
    Point shape_rt = shape.getRightTop();

    double x1 = this_lb.getX();
    double y1 = this_lb.getY();
    double x2 = this_rt.getX();
    double y2 = this_rt.getY();
    double x3 = shape_lb.getX();
    double y3 = shape_lb.getY();
    double x4 = shape_rt.getX();
    double y4 = shape_rt.getY();

    // check if MBB don't intersect
    if (x4 < x1 || x3 >= x2 || y4 < y1 || y3 >= y2)
        return NO_INTERSECTION;

    int result = 0;

    // check if there is a part of another shape to the left
    if (x3 < x1 && x4 > x1)
        result |= LEFT;

    // to the right
    if (x3 <= x2 && x4 >= x2)
        result |= RIGHT;

    // to the bottom
    if (y3 < y1 && y4 > y1)
        result |= BOTTOM;

    // to the top
    if (y3 <= y2 && y4 >= y2)
        result |= TOP;

    return result;
}
