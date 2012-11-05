/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <iostream>

#include "ParamArray.h"

//**************************************************************************
// KEYS ACCESSING.
//**************************************************************************

void ParamArray::addKey(std::string key, int value)
{
    this -> map[key] = value;
}

int ParamArray::getValue(std::string key) const throw(EParamArrayBadKey)
{
    std::map <std::string, int> :: const_iterator iter = this -> map.find(key);

    if(iter == map.end())
    {
        std::cerr << "[WARN] ParamArray: tried to get value by key, which " <<
                     "doesn't seem to be existed (key is '" << key << "')." <<
                     std::endl;

        throw EParamArrayBadKey();
    }

    return iter -> second;
}

bool ParamArray::removeKey(std::string key)
{
    std::map <std::string, int> :: const_iterator iter = this -> map.find(key);

    if(iter == map.end())
    {
        std::cerr << "[WARN] ParamArray: tried to delete key, which doesn't " <<
                     "seem to be be existed (key is '" << key << "')." <<
                     std::endl;

        return false;
    }

    this -> map.erase(iter);

    return true;
}
