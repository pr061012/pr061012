/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "ObjectHeap.h"

#include "../../../common/BasicDefines.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

ObjectHeap::ObjectHeap()
{
    data.resize(AMNT_OBJECT_TYPES + 1);
}

ObjectHeap::~ObjectHeap()
{
}

//******************************************************************************
// GETTING TYPE AMOUNT
//******************************************************************************

unsigned int ObjectHeap::getAmount()
{
    return data[0].size();
}

unsigned int ObjectHeap::getTypeAmount(ObjectType type)
{
    // Get type of object.
    int type_id = static_cast<int>(type);

    return data[type_id+1].size();
}

//******************************************************************************
// ADDING/REMOVING ELEMENTS.
//******************************************************************************

bool ObjectHeap::push(Object* object)
{
    // Getting type of the object.
    int type_id = static_cast<int>(object -> getType());
    bool exist = false;

    // Check for exist object in heap.
    for(unsigned int i = 0; i < data[type_id+1].size(); i++)
    {
        if (data[type_id+1][i] == object)
        {
            exist = true;
        }
    }

    // Add object in heap.
    if (!exist)
    {
        data[type_id + 1].push_back(object);
        data[0].push_back(object);
    }

    return !exist;
}

int counter = 0;

bool ObjectHeap::remove(Object* object)
{
    bool del = false;
    counter++;
    // Position in TypeObject array.
    unsigned int pos = 0;
    // Type remove object.

    const ObjectType my_type = object -> getType();
    // Getting type of the object in int.
    int type_int = static_cast<int>(my_type);

    // Find object.
    for(unsigned int i = 0; i < data[0].size(); i++)
    {
        if ((data[0][i] -> getType()) == my_type)
        {
            if (data[0][i] == object)
            {
                    data[0].erase(data[0].begin() + i);
                    del = true;
                    break;
            }
            pos++;
        }
    }

    // Delete object from type array.
    if (del)
    {
        data[type_int + 1].erase(data[type_int + 1].begin() + pos);
    }

    return del;
}
