/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef CONTROLLER_H__
#define CONTROLLER_H__

#include <vector>

#include "../../model/World/World.h"
#include "../Performer/Performer.h"

/**
 * @class Controller
 * @brief Class controls the world!
 */
class Controller
{
public:
    //*************************************************************************
    // CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor
     * @param world world
     */
    Controller(World& world);

    /**
     * @brief Destructor
     */
    ~Controller();

    //*************************************************************************
    // STEP
    //*************************************************************************
    
    /**
     * @brief Tries to make all requested actions in the world.
     */
    void step();

private:
    
    //*************************************************************************
    // ATTRIBUTES
    //*************************************************************************
    
    /// World
    World& world;

    // List of performers
    std::vector <Performer *> performers;
};

#endif
