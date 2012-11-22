/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef MINING_PERFORMER_H__
#define MINING_PERFORMER_H__

#include "../Performer.h"
#include "../../../model/World/World.h"
#include "../../../model/World/Object/Resource/Resource.h"
#include "../../../model/World/Object/Tool/Tool.h"


/**
 * @class MiningPerformer
 * @brief Performs a mining if it is possible
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
    MiningPerformer(World * world);

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

};

#endif
