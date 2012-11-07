/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef MOVEMENT_PERFORMER_H__
#define MOVEMENT_PERFORMER_H__

#include "../Performer.h"

/**
 * @class CreationPerformer
 * @brief Performs a create if it is possible
 */
class CreationPerformer : public Performer
{
public:
    
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor
     * @param indexator indexator
     */
    CreationPerformer();

    /**
     * @brief Destructor
     */
    ~CreationPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if an object can create
     * @param action a request for creation
     */
    void perform(Action& action);

private:

    //*************************************************************************
    //  ATTRIBUTES
    //*************************************************************************

};

#endif
