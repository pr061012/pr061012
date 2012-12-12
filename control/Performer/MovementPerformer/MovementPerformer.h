/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef MOVEMENT_PERFORMER_H__
#define MOVEMENT_PERFORMER_H__

#include "../Performer.h"
#include "../../../model/World.h"

/**
 * @class MovementPerformer
 * @brief Lets objects move another objects
 */
class MovementPerformer : public Performer
{
public:
    
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor for a particular world
     * @param world controlled world
     */
    MovementPerformer(World * world);

    /**
     * @brief Destructor
     */
    ~MovementPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if an object can be moved and move it
     * @param action a request for moving
     */
    void perform(Action& action);

};

#endif
