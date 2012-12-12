/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef CONTROLLER_H__
#define CONTROLLER_H__

#include <vector>

#include "../../model/World.h"
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
    Controller(World* world);

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

    /**
     * @brief Destroys an object.
     * @param object object to be destroyed.
     */
    void destroy(Object * object);
    
    //*************************************************************************
    // ATTRIBUTES
    //*************************************************************************
    
    /// World
    World * world;

    /// List of performers
    std::vector <Performer *> performers;

    /// Swap buffer from hidden to visible objects
    ObjectHeap hiddenToVisible;

    /// Swap buffer from visible to hidden objects
    ObjectHeap visibleToHidden;

    /// Actions accumulator
    std::vector<Action*> actions;

    /// Steps to generate weather.
    int weather_steps;
    /// Steps to generate resource.
    int resource_steps;
    /// Steps to generate creature.
    int creature_steps;
};

#endif
