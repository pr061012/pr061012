/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Frame.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR
//******************************************************************************

Frame::Frame (Point center, int type, double size )
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

Frame::~Frame ()
{
}

//  
// Methods
//  


// Accessor methods
//  

void Frame::setCenter ( Point new_var )
{
    center = new_var;
}

Point Frame::getCenter ( )
{
    return center;
}

void Frame::setType(int type)
{
    this -> type = (ShapeType) type;
}

int Frame::getType()
{
    return type;
}

double Frame::setSize()
{
    this -> size = size;
}

double Frame::getSize()
{
    return size;
}



// Other methods
//




