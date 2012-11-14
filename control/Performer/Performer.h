/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef PERFORMER_H__
#define PERFORMER_H__

#include "../../model/World/Action/Action.h"

/**
 * @class Performer
 * @brief Class is an interface for processing messages that come from the world
 *      * It checks if an action is possible to take place in the world and
 *      * performs it
 */

class Performer
{
public:
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Destructor
     */
    virtual ~Performer();

    /**
     * @brief Empty constructor
     */
    Performer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    /**
     * @brief Performs an action if it is possible
     */
    virtual void perform(Action& action) = 0;
};

#endif
