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
     * @param world controlled world
     */
    DroppingPerformer(World* world, ObjectHeap * buffer);

    /**
     * @brief Destructor
     */
    ~DroppingPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if an object can drop an object
     * @param action a request for dropping item
     */
    void perform(Action& action);

private:
    
    /// Buffer for dropping objects
    ObjectHeap * buffer;

};

#endif
