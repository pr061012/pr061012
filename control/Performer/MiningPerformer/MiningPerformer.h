/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef MINING_PERFORMER_H__
#define MINING_PERFORMER_H__

#include "../Performer.h"
#include "../../../model/World/Indexator/Indexator.h"
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
    MiningPerformer(Indexator& indexator);

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

    /// The reference to worlds indexator
    Indexator& indexator;

};

#endif
