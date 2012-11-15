/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef TRAVELING_PERFORMER_H__
#define TRAVELING_PERFORMER_H__

#include "../Performer.h"
#include "../../../model/World/Indexator/Indexator.h"

/**
 * @class TravelingPerformer
 * @brief Performs a move if it is possible
 */
class TravelingPerformer : public Performer
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
    TravelingPerformer(const double world_size, Indexator* indexator);

    /**
     * @brief Destructor
     */
    ~TravelingPerformer();

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
    const double world_size;
    
    /// The reference to worlds indexator
    Indexator* indexator;
};

#endif
