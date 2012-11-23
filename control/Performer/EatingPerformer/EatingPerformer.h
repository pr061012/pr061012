/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef EATING_PERFORMER_H__
#define EATING_PERFORMER_H__

#include "../Performer.h"
#include "../../../model/World/World.h"

/**
 * @class EatingPerformer
 * @brief Lets objects eat
 */
class EatingPerformer : public Performer
{
public:
    
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor for a particular world
     * @param world controlled world
     */
    EatingPerformer(World * world);

    /**
     * @brief Destructor
     */
    ~EatingPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if an object can eat objects
     * @param action a request for eating
     */
    void perform(Action& action);

};

#endif
