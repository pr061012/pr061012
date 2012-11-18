/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <iostream>
#include <cmath>

#include "Shape.h"
#include "../../../common/BasicDefines.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Shape::Shape (Vector center, int type, double size )
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

void Shape::setCenter ( Vector new_var )
{
    last_center = center;
    center = new_var;
}

const Vector& Shape::getCenter ( ) const
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
            left_bottom = Vector(-size/2, -size/2);
            right_top = -left_bottom;
            break;
    }
}

Vector Shape::getLeftBottom() const
{
    return center + left_bottom;
}

Vector Shape::getRightTop() const
{
    return center + right_top;
}

Vector Shape::getLastCenter()
{
    return last_center;
}

//******************************************************************************
// HIT-TEST METHODS.
//******************************************************************************

// checks hittest with a vector
bool Shape::hitTest (const Vector& vector) const
{
    switch(type)
    {
        case CIRCLE:
            // if a distance between a vector and a circle center is less than
            // radius, return true
            if (center.getDistance(vector) - size/2 <= MATH_EPSILON)
            {
                return true;
            }
            break;

        case SQUARE:
            // if a vector lies nearer than sides of a square, return true
            if (fabs(center.getY() - vector.getY()) - size/2 <= MATH_EPSILON &&
                fabs(center.getX() - vector.getX()) - size/2 <= MATH_EPSILON)
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
    switch(type)
    {
        case CIRCLE:
            switch(shape.getType())
            {
                // if sum of radiuses is more than distance between centers,
                // return true
                case CIRCLE:
                    if (center.getDistance(shape.getCenter()) <=
                        (size + shape.getSize())/ 2)
                    {
                        return true;
                    }
                    break;

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
                    Vector lb = getLeftBottom();
                    if (shape.hitTest(lb))
                    {
                        return true;
                    }

                    Vector rt = getRightTop();
                    if (shape.hitTest(rt))
                    {
                        return true;
                    }

                    Vector lt = (Vector(lb.getX(), rt.getY()));
                    Vector rb = Vector(rt.getX(), lb.getY());

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

                    lt = (Vector(lb.getX(), rt.getY()));
                    rb = Vector(rt.getX(), lb.getY());

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
    Vector lb = square.getLeftBottom();
    Vector rt = square.getRightTop();
    Vector lt = Vector(lb.getX(), rt.getY());
    Vector rb = Vector(rt.getX(), lb.getY());

    // a square can have circle's center inside
    if (square.hitTest(circle.getCenter()))
    {
        return true;
    }

    // cicle can intersect any side of the square
    if (circleOverlapsSegment(circle, lt, rt) ||
          circleOverlapsSegment(circle, lb, rb) ||
          circleOverlapsSegment(circle, lb, lt) ||
          circleOverlapsSegment(circle, rb, rt))
    {
        return true;
    }

    return false;
}

// check if a circle intersects segment
bool Shape::circleOverlapsSegment(Shape shape, Vector pt1, Vector pt2) const
{
    Vector project = shape.getCenter().project(pt1, pt2);

    // check if sement line is closer than radius and if 
    // one of the segments end lie inside a shape or
    // if a segment crosses circle with ends outside
    return (shape.getCenter().getDistanceToLine(pt1, pt2) < shape.getSize()/2)
            && (shape.hitTest(pt1) || shape.hitTest(pt2) ||
                Vector::scalarProduct(pt2 - project, pt1 - project) < 0);
}

// Calculates intersections
int Shape::intersect(const Shape& shape)
{
    // copy data
    Vector this_lb = this -> getLeftBottom();
    Vector this_rt = this -> getRightTop();
    Vector shape_lb = shape.getLeftBottom();
    Vector shape_rt = shape.getRightTop();

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
