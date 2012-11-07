/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <iostream>

#include "ParamArray.h"

//**************************************************************************
// KEYS ACCESSING.
//**************************************************************************

template <class Type> void ParamArray::addKey(std::string key, Type value)
{
    Type * copy = new Type(value);
    this -> map[key] = copy;
}

template <class Type> Type ParamArray::getValue(std::string key) const throw(EParamArrayBadKey)
{
    std::map <std::string, void *> :: const_iterator iter = this -> map.find(key);

    if(iter == map.end())
    {
        std::cerr << "[WARN] ParamArray: tried to get value by key, which " <<
                     "doesn't seem to be existed (key is '" << key << "')." <<
                     std::endl;

        throw EParamArrayBadKey();
    }

    return *(dynamic_cast<Type *>(iter -> second));
}

template <class Type> bool ParamArray::removeKey(std::string key)
{
    std::map <std::string, void *> :: const_iterator iter = this -> map.find(key);

    if(iter == map.end())
    {
        std::cerr << "[WARN] ParamArray: tried to delete key, which doesn't " <<
                     "seem to be be existed (key is '" << key << "')." <<
                     std::endl;

        return false;
    }

    delete dynamic_cast<Type *>(iter -> second);
    this -> map.erase(iter);

    return true;
}
