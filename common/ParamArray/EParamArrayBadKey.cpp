/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "EParamArrayBadKey.h"

const char * EParamArrayBadKey::what() const throw()
{
    return "ParamArray: tried to access value with nonexistent key.";
}
