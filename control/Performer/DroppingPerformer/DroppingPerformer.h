/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef DROPPING_PERFORMER_H__
#define DROPPING_PERFORMER_H__

#include "../Performer.h"
#include "../../../model/World/World.h"

/**
 * @class DroppingPerformer
 * @brief Performs a drop if possible
 */
class DroppingPerformer : public Performer
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
    DroppingPerformer(World* world);

    /**
     * @brief Destructor
     */
    ~DroppingPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if an object can move and move it
     * @param action a request for moving
     */
    void perform(Action& action);

private:

    //*************************************************************************
    //  ATTRIBUTES
    //*************************************************************************
    
    /// Size of the world
    World * world;
};

#endif
