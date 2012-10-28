#include "ViewObject.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

ViewObject::ViewObject(ObjectType newtype, double newx, double newy)
{
    type = newtype;
    newx    = x;
    newy    = y;
}


ViewObject::~ViewObject()
{

}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void ViewObject::setType(ObjectType new_var)
{
    type = new_var;
}

ObjectType ViewObject::getType()
{
    return type;
}

double ViewObject::getX()
{
    return x;
}

double ViewObject::getY()
{
    return y;
}

void ViewObject::setY(ObjectType new_var)
{
    y = new_var;
}

void ViewObject::setX(ObjectType new_var)
{
    x = new_var;
}
