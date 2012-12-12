/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef REGENERATION_PERFORMER_H
#define REGENERATION_PERFORMER_H

#include "../Performer.h"
#include "../../../model/World.h"

/**
 * @class RegenerationPerformer
 * @brief Performs a regeneration if it is possible
 */
class RegenerationPerformer : public Performer
{
public:
    
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor
     */
    RegenerationPerformer(World * world);

    /**
     * @brief Destructor
     */
    ~RegenerationPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if
     * @param action a request for
     */
    void perform(Action& action);

};
#endif
