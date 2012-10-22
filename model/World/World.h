/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "../ObjectHeap/ObjectHeap.h"


/**
  * @class World
  * @brief Class containing methods for primary model interaction
  */

class World
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

	/**
     * @brief Constructor
	 */
    World();

	/**
     * @brief Destructor
	 */
    virtual ~World();

	/**
     * @brief World generation by given seed.
     * @param rand_seed
	 */
    World(int rand_seed);

	/**
     * @brief Load saved world from file.
     * @param filepath
	 */
    World(std::string filepath);

    //******************************************************************************
    // BASE METHODS.
    //******************************************************************************

	/**
     * @brief Save world to file.
     * @param filepath
	 */
    void save(std::string filepath);

    /**
     * @brief Update world state
     */
    void step();

private:

    /// Heap containing all World's objects
    ObjectHeap all_objects;

public:

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

	/**
     * @brief Set the value of all_objects.
	 * @param new_var the new value of all_objects
	 */
    void setAllObjects(ObjectHeap new_var);

	/**
     * @brief Get the value of all_objects.
	 * @return the value of all_objects
	 */
    ObjectHeap getAllObjects();
private:


};

#endif // WORLD_H
