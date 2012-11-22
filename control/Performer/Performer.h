/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef PERFORMER_H__
#define PERFORMER_H__

#include "../../model/World/Action/Action.h"
#include "../../model/World/World.h"

/**
 * @class Performer
 * @brief Class is an interface for processing messages that come from the world
 *      * It checks if an action is possible to take place in the world and
 *      * performs it
 */

class Performer
{
private:
    
    /**
     * @brief Empty constructor
     */

    Performer();
public:
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Destructor
     */
    virtual ~Performer();

    /**
     * @brief Constructs performer for current world pointer
     */
    Performer(World * world);

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    /**
     * @brief Performs an action if it is possible
     */
    virtual void perform(Action& action) = 0;

protected:
    
    /// Pointer to controlled world
    World * world;
};

#endif
