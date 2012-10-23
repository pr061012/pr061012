#include "Frame.h"

// Constructors/Destructors
//  

Frame::Frame (Point center, int type, double size )
{
    this -> type = (ShapeType) type;
    this -> center = center;
    this -> size = size;
    this -> last_center = center;
    switch(type)
    {
        case CIRCLE:
            left_bottom = Point(size, size);
             = Point(size, size);
    }
    left_bottom = center
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




