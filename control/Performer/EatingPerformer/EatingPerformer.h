/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef EATING_PERFORMER_H__
#define EATING_PERFORMER_H__

#include "../Performer.h"
#include "../../../model/World/World.h"

/**
 * @class EatingPerformer
 * @brief Performs a move if it is possible
 */
class EatingPerformer : public Performer
{
public:
    
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor for a particular world
     * @param world_size size of the world
     * @param indexator indexator
     */
    EatingPerformer(World * world);

    /**
     * @brief Destructor
     */
    ~EatingPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if an object can move and move it
     * @param action a request for moving
     */
    void perform(Action& action);

};

#endif
