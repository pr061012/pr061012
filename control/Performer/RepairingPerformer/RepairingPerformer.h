/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef REPAIRING_PERFORMER_H__
#define REPAIRING_PERFORMER_H__

#include "../Performer.h"

/**
 * @class RepairingPerformer
 * @brief Performs a repair if it is possible
 */
class RepairingPerformer : public Performer
{
public:
    
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor
     */
    RepairingPerformer();

    /**
     * @brief Destructor
     */
    ~RepairingPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if an object can repair and repair it
     * @param action a request for repairing
     */
    void perform(Action& action);

private:

    //*************************************************************************
    //  ATTRIBUTES
    //*************************************************************************

};

#endif
