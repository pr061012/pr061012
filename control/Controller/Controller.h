#ifndef CONTROLLER_H_
#define CONTROLLER_H_

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
     * @brief Empty constructor
     */
    Controller();

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
    step();

private:
    
    //*************************************************************************
    // ATTRIBUTES
    //*************************************************************************
    
    /// World
    World& world;

    // List of performers
    Performer * performers;
}

#endif
