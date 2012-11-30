/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <sstream>

#include "ObjectHeap.h"

#include "../../../common/BasicDefines.h"

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

uint ObjectHeap::getAmount()
{
    return data[0].size();
}

uint ObjectHeap::getTypeAmount(ObjectType type)
{
    // Get type of object.
    int type_id = static_cast<int>(type);

    return data[type_id+1].size();
}

//******************************************************************************
// ADDING/REMOVING ELEMENTS.
//******************************************************************************

bool ObjectHeap::push(Object* obj)
{
    data[obj -> getType() + 1].insert(std::pair<uint, Object*>(obj -> getObjectID(), obj) );
    data[0].insert(std::pair<uint,Object*>(obj -> getObjectID(), obj) );
}


bool ObjectHeap::remove(Object* object)
{
    data[object -> getType() + 1].erase(object -> getObjectID());
    data[0].erase(object -> getObjectID());
}

void ObjectHeap::clear()
{
    for (uint i = 0; i <= AMNT_OBJECT_TYPES; i++)
    {
        data[i].clear();
    }
}

//******************************************************************************
// PRINTING CONTENTS.
//******************************************************************************

std::string ObjectHeap::printIDs(std::string indent, uint columns) const
{
    std::stringstream ss;
    uint cur_column = 1;

    ObjectHeap::iterator iter;
    for (iter = const_cast<ObjectHeap*>(this) -> begin(); iter != const_cast<ObjectHeap*>(this)->end(); iter++)
    {
        ss << indent << (*iter) -> getObjectID();

        if (cur_column++ == columns || iter++ == const_cast<ObjectHeap*>(this)-> end())
        {
            iter--;
            cur_column = 1;
            ss << std::endl;
        }
    }

    return ss.str();
}

//**************************************************************************
// ITERATOR
//**************************************************************************


