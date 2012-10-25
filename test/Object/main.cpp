/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <iostream>
#include <assert.h>

#include "../../model/World/Object/Object.h"

int main()
{
    ObjectType type=RESOURCE;
    ///Create Object
    Object object(type);


    //**************************************************************************
    // TEST ACCESSORS.
    //**************************************************************************

    ///Test health state
    object.setHealth(100);
    assert(object.getHealth()==100);

    ///Test type state
    assert(object.getType()==RESOURCE);

    return 0;
}
