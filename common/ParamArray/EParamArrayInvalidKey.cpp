/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include <sstream>

#include "EParamArrayInvalidKey.h"

EParamArrayInvalidKey::EParamArrayInvalidKey(std::string key_name) :
    key_name(key_name)
{
}

std::string EParamArrayInvalidKey::getKeyName()
{
    return this -> key_name;
}

const char* EParamArrayInvalidKey::what() const throw()
{
    std::stringstream ss;
    ss << "ParamArray: tried to access value with nonexistent (" <<
          this -> key_name << ") key.";
    return ss.str().c_str();
}
