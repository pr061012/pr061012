/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include <cstdlib>

#include "../BasicDefines.h"
#include "DoubleComparison.h"
#include "Random.h"

int Random::int_num(int top_boundary)
{
    if (top_boundary == 0)
    {
        return 0;
    }

    return rand() % top_boundary;
}

double Random::double_num(double top_boundary)
{
    if (DoubleComparison::areEqual(top_boundary, 0))
    {
        return 0;
    }

    top_boundary *= 1000000;
    return (rand() % ((int) top_boundary)) / 1000000.0;
}

int Random::int_range(int low_boundary, int top_boundary)
{
    return Random::int_num(top_boundary - low_boundary) + low_boundary;
}

double Random::double_range(double low_boundary, double top_boundary)
{
    return Random::double_num(top_boundary - low_boundary) + low_boundary;
}
