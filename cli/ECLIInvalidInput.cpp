/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "ECLIInvalidInput.h"

ECLIInvalidInput::ECLIInvalidInput(std::string reason) :
    std::exception(),
    reason(reason)
{
}


const char * ECLIInvalidInput::what() const throw()
{
    return std::string("Error: " + this -> reason + ".\n").c_str();
}
