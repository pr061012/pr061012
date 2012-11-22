/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef PICKUP_MASTER_H__
#define PICKUP_MASTER_H__

#include "../Performer.h"
#include "../../../model/World/World.h"

/**
 * @class PickupMaster
 * @brief No comments
 */
class PickupMaster : public Performer
{
public:
    
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor for a particular world
     * @param world_size size of the world
     * @param world world
     */
    PickupMaster(World* world);

    /**
     * @brief Destructor
     */
    ~PickupMaster();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if we can pick objects
     * @param action a request for moving
     */
    void perform(Action& action);

};

#endif
