/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "EInvalidResPath.h"

EInvalidResPath::EInvalidResPath(std::string res_path) :
    std::exception(),
    res_path(res_path)
{
}

std::string EInvalidResPath::getResPath()
{
    return this -> res_path;
}

const char * EInvalidResPath::what() const throw()
{
    return "Failed to load resource: invalid path.";
}
