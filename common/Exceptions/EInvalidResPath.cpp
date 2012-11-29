/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include <sstream>

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

const char* EInvalidResPath::what() const throw()
{
    std::stringstream ss;
    ss << "Failed to load resource: invalid path (" << this -> res_path << ")";
    return ss.str().c_str();
}
