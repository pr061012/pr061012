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
    return NULL;
}

Object* ObjectHeap::next(ObjectType type)
{
    return NULL;
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
    return true;
}

bool ObjectHeap::remove(Object* object)
{
    return true;
}
