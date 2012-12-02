/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include <cfloat>
#include <cmath>

#include "DoubleComparison.h"

#define EPSILON DBL_EPSILON * 16 * 100000

bool DoubleComparison::areEqual(double a, double b)
{
    return fabs(a - b) <= EPSILON * fmax(fabs(a), fabs(b));
}

bool DoubleComparison::areNotEqual(double a, double b)
{
    return !areEqual(a, b);
}

bool DoubleComparison::isGreater(double a, double b)
{
    return (a - b) > EPSILON * fmax(fabs(a), fabs(b));
}

bool DoubleComparison::isLess(double a, double b)
{
    return (b - a) > EPSILON * fmax(fabs(a), fabs(b));
}
