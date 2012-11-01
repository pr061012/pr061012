/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "ObjectFactory.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

ObjectFactory::ObjectFactory()
{
    ObjectFactory(NULL);
}

ObjectFactory::ObjectFactory(ObjectHeap *list)
{
    this -> list = list;
}

ObjectFactory::~ObjectFactory()
{
}

//******************************************************************************
// OBJECT'S CREATION.
//******************************************************************************

Object* ObjectFactory::createObject(ObjectType type, std::map<std::string, void *> params)
{

}
