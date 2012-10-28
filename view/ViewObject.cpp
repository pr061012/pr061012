#include "ViewObject.h"

ViewObject::ViewObject();

ViewObject::~ViewObject();

void ViewObject::setType(ObjectType new_var)
{
    type = new_var;
}

ObjectType ViewObject::getType()
{
    return type;
}
