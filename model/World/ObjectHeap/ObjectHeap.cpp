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
    Object* ret;

    ret = data[0][position[0]];
    position[0]++;

    return ret;
}

Object* ObjectHeap::next(ObjectType type)
{
    Object* ret;
    /// Get type of object
    int type_int = static_cast<int>(type) + 1;

    ret = data[type_int][position[type_int]];
    position[type_int]++;

    return ret;
}

unsigned int ObjectHeap::getTypeAmount(ObjectType type)
{
    /// Get type of object
    int type_int = static_cast<int>(type);
    int size = data[type_int]->size();

    return static_cast<unsigned int>(size);
}

//******************************************************************************
// ADDING/REMOVING ELEMENTS.
//******************************************************************************

bool ObjectHeap::push(Object* object)
{
    data[static_cast<int>(object->getType()) + 1]->push_back();
    data[0]->push_back();

    return true;
}

bool ObjectHeap::remove(Object* object)
{
    bool del = false;
    for(int i=0; i<data.size();i++)
    {
        for(int j=0; j<data[i]->size();j++)
        {
            if (data[i][j]==object)
            {
                data[i]->erase(j);
            }
            del = true;
        }
    }
    return del;
}
