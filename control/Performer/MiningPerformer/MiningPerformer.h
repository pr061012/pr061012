/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef MOVEMENT_PERFORMER_H__
#define MOVEMENT_PERFORMER_H__

#include "../Performer.h"

/**
 * @class MiningPerformer
 * @brief Performs a mine if it is possible
 */
class MiningPerformer : public Performer
{
public:
    
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor
     */
    MiningPerformer();

    /**
     * @brief Destructor
     */
    ~MiningPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if an object can mine and mine it
     * @param action a request for mining
     */
    void perform(Action& action);

private:

    //*************************************************************************
    //  ATTRIBUTES
    //*************************************************************************
};

#endif
