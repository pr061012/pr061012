/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#ifndef DOUBLE_COMPARISON_H
#define DOUBLE_COMPARISON_H

#include <cfloat>

/**
 * @brief Interface for double comparison.
 *        The following definitions of functions are from Knuth's ''The art of
 *        computer programming''.
 */
class DoubleComparison
{
public:
    /**
     * @brief  Comparison ==.
     * @param  a    first double number
     * @param  b    second double number
     * @return a == b
     */
    static bool areEqual(double a, double b)
    {
        return fabs(a - b) <= DBL_EPSILON * fmax(fabs(a), fabs(b));
    }

    /**
     * @brief  Comparison !=.
     * @param  a    first double number
     * @param  b    second double number
     * @return a != b
     */
    static bool areNotEqual(double a, double b)
    {
        return !areEqual(a, b);
    }

    /**
     * @brief  Comparison >.
     * @param  a    first double number
     * @param  b    second double number
     * @return a > b
     */
    static bool isGreater(double a, double b)
    {
        return (a - b) > DBL_EPSILON * fmax(fabs(a), fabs(b));
    }

    /**
     * @brief  Comparison <.
     * @param  a    first double number
     * @param  b    second double number
     * @return a < b
     */
    static bool isLess(double a, double b)
    {
        return (b - a) > DBL_EPSILON * fmax(fabs(a), fabs(b));
    }
};

#endif // DOUBLE_COMPARISON_H
