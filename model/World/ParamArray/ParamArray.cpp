/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "ParamArray.h"

//**************************************************************************
// KEYS ACCESSING.
//**************************************************************************

void ParamArray::addKey(std::string key, int value)
{
    this -> map[key] = value;
}

int ParamArray::getValue(std::string key) const
{
    std::map <std::string, int> :: const_iterator iter = this -> map.find(key);

    if(iter == map.end())
    {
        // TODO: Throw an exception.
    }

    return iter -> second;
}

bool ParamArray::removeKey(std::string key)
{
    std::map <std::string, int> :: const_iterator iter = this -> map.find(key);

    if(iter == map.end())
    {
        return false;
    }

    this -> map.erase(iter);

    return true;
}
