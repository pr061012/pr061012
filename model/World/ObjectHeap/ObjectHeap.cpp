/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "ObjectHeap.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

ObjectHeap::ObjectHeap()
{

}

ObjectHeap::~ObjectHeap()
{

}

//******************************************************************************
// GETTING NEXT ELEMENTS.
//******************************************************************************

Object* ObjectHeap::next()
{
    Object* object = new Object();
    return object;
}

Object* ObjectHeap::next(ObjectType type)
{
    Object* object = new Object();
    object -> setType(type);
    return object;
}

unsigned int ObjectHeap::getTypeAmount(ObjectType)
{
    return 0;
}

//******************************************************************************
// ADDING/REMOVING ELEMENTS.
//******************************************************************************

bool ObjectHeap::push(Object* object)
{
    return True;
}

bool ObjectHeap::remove(Object* object)
{
    return True;
}
