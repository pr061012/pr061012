/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <iostream>
#include <cmath>
#include <vector>

#include "Shape.h"
#include "../Math/DoubleComparison.h"

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

void Shape::setType(ShapeType type)
{
    this -> type = type;
}

ShapeType Shape::getType() const
{
    return type;
}

std::string Shape::getTypeName() const
{
    switch (type)
    {
        case CIRCLE: return "circle"; break;
        case SQUARE: return "square"; break;
    }

    return "unknown";
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

std::vector<Vector> Shape::getVertices() const
{
    std::vector<Vector> result;
    switch(type)
    {
        case CIRCLE:
            break;
            
        case SQUARE:
            result.push_back(center + left_bottom);
            result.push_back(center + Vector(-size/2, size/2));
            result.push_back(center + right_top);
            result.push_back(center + Vector(size/2, -size/2));
            break;
    }
    return result;
}

//******************************************************************************
// HIT-TEST METHODS.
//******************************************************************************

// checks hittest with a point
bool Shape::hitTest (const Vector& point) const
{
    switch(type)
    {
        case CIRCLE:
            // if a distance between a point and a circle center is less than
            // radius, return true
            if (DoubleComparison::isLess(center.getDistance(point), size/2))
            {
                return true;
            }
            break;

        case SQUARE:
            // if a point lies nearer than sides of a square, return true
            if (DoubleComparison::isLess(fabs(center.getY() - point.getY()), 
                                         size/2) &&
                DoubleComparison::isLess(fabs(center.getX() - point.getX()),
                                         size/2))
            {
                return true;
            }
            break;
    }
    return false;
}

// check hittest with a segment
bool Shape::hitTest (const Vector& first, const Vector& second) const
{
    Vector point;
    std::vector<Vector> vertices = getVertices();
    switch(type)
    {
        case CIRCLE:
            point = this -> getCenter().project(first, second);

            // check if sement line is closer than radius and if 
            // one of the segments end lie inside a shape or
            // if a segment crosses circle with ends outside
            return DoubleComparison::isLess(
                        this -> getCenter().getDistanceToLine(first, second),
                        this -> getSize() / 2) && 
                    (this -> hitTest(first) || this -> hitTest(second) ||
                        DoubleComparison::isLess(
                            Vector::scalarProduct(second - point, 
                                                  first - point), 0));
            break;
        
        case SQUARE:
            // Check if segment ends lie inside the square.
            if (hitTest(first) || hitTest(second))
            {
                return true;
            }

            vertices = getVertices();
            // Check if segment intersects any of sides.
            for (uint i = 0; i < 4; i++)
            {
                point = Vector::getLinesIntersection(first, second, 
                                            vertices[i], vertices[(i+1) % 4]);
                if (!isnan(point.getX()))
                {
                    double t = point.getLineParameter(first, second);
                    if (t > 0 && t < 1) 
                    {
                        return true;
                    }
                }
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
                    if (DoubleComparison::isLess(center.getDistance(shape.getCenter()),
                                                 (size + shape.getSize()) / 2))
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
    // and vice versa
    if (square.hitTest(circle.getCenter()) ||
        circle.hitTest(square.getCenter()))
    {
        return true;
    }

    // cicle can intersect any side of the square
    if (circle.hitTest(lt, rt) ||
          circle.hitTest(lb, rb) ||
          circle.hitTest(lb, lt) ||
          circle.hitTest(rb, rt))
    {
        return true;
    }

    return false;
}

//**********************************************************
// UNUSED
//**********************************************************

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
