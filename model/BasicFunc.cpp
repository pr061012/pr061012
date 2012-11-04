/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "BasicFunc.h"

//******************************************************************************
// STATIC FUNCTIONS.
//******************************************************************************

static inline int randFromRange(int low_boundary, int top_boundary)
{
    return rand() % (top_boundary - low_boundary) + low_boundary + 1;
}
