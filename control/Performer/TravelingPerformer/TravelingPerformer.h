/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef TRAVELING_PERFORMER_H__
#define TRAVELING_PERFORMER_H__

#include "../Performer.h"

/**
 * @class TravelingPerformer
 * @brief Allows objects to travel around the world if it is possible
 */
class TravelingPerformer : public Performer
{
public:
    
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor for a particular world
     * @param world controlled world
     */
    TravelingPerformer(World * world);

    /**
     * @brief Destructor
     */
    ~TravelingPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if an object can travel and moves it
     * @param action a request for moving
     */
    void perform(Action& action);
};

#endif
