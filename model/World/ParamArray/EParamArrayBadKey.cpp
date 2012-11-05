#include "EParamArrayBadKey.h"

const char * EParamArrayBadKey::what() const throw()
{
    return "ParamArray: tried to access value with nonexistent key.";
}
