/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <sstream>
#include <map>
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

uint ObjectHeap::getAmount() const
{
    return data[0].size();
}

uint ObjectHeap::getTypeAmount(ObjectType type) const
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
    std::pair< std::map<uint, Object*>::iterator, bool> ret;
    ret = data[obj -> getType() + 1].insert(std::pair<uint, Object*>(obj -> getObjectID(), obj) );
    if (ret.second)
    {
        data[0].insert(std::pair<uint,Object*>(obj -> getObjectID(), obj));
    }
    return ret.second;
}


bool ObjectHeap::remove(Object* object)
{
    uint ret;
    ret = data[object -> getType() + 1].erase(object -> getObjectID());
    if (ret)
    {
        data[0].erase(object -> getObjectID());
    }
    return ret != 0 ? true : false;
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
    if (this -> getAmount() == 0)
    {
        return indent + "empty\n";
    }

    std::stringstream ss;
    uint cur_column = 1;

    ObjectHeap::const_iterator iter;
    for (iter = this -> begin(); iter != this -> end(); iter++)
    {
        ss << indent << (*iter) -> getObjectID();
        cur_column++;
        if (cur_column == columns)
        {
            cur_column = 1;
            ss << std::endl;
        }
    }
    ss << std::endl;

    return ss.str();
}

//**************************************************************************
// ITERATOR
//**************************************************************************


