/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <assert.h>
#include "../../model/World/ObjectHeap/ObjectHeap.h"


int main()
{
    //**************************************************************************
    // TEST CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    ///Create ObjectHeap
    ObjectHeap* heap = new ObjectHeap();

    ///Create Object
    Object obj(RESOURCES);
    //**************************************************************************
    // TEST GETTING NEXT ELEMENTS.
    //**************************************************************************
    Object* obj_2=heap->next();
    //**************************************************************************
    // TEST ADDING/REMOVING ELEMENTS.
    //**************************************************************************
    heap->push(&obj);
}
