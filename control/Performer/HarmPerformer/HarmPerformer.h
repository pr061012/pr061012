/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef MOVEMENT_PERFORMER_H__
#define MOVEMENT_PERFORMER_H__

#include "../Performer.h"

/**
 * @class HarmPerformer
 * @brief Performs a harm if it is possible
 */
class HarmPerformer : public Performer
{
public:
    
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor
     */
    HarmPerformer();

    /**
     * @brief Destructor
     */
    ~HarmPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if an object can harm
     * @param action a request for harm
     */
    void perform(Action& action);

private:

    //*************************************************************************
    //  ATTRIBUTES
    //*************************************************************************

};

#endif
