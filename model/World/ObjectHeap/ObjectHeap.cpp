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
// GETTING TYPE AMOUNT
//******************************************************************************

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
