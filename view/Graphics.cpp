#include "Graphics.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Graphics::Graphics(ObjectType newtype, double newx, double newy)
{
    type = newtype;
    newx    = x;
    newy    = y;
}


Graphics::~Graphics()
{

}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void Graphics::setType(ObjectType new_var)
{
    type = new_var;
}

ObjectType Graphics::getType()
{
    return type;
}

double Graphics::getX()
{
    return x;
}

double Graphics::getY()
{
    return y;
}

void Graphics::setY(ObjectType new_var)
{
    y = new_var;
}

void Graphics::setX(ObjectType new_var)
{
    x = new_var;
}
