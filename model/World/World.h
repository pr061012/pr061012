/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef WORLD_H
#define WORLD_H

#include <string.h>
#include <stdlib.h>
#include <vector>
#include "IWorld.h"
#include "ObjectHeap/ObjectHeap.h"
#include "ObjectFactory/ObjectFactory.h"
#include "../../view/ViewObject/ViewObject.h"
#include "Indexator/Indexator.h"


/**
 * @brief Default values for max x and y.
 */
#define DEFAULT_WIDTH 5000
#define DEFAULT_HEIGHT 5000

/**
  * @class World
  * @brief Class containing methods for primary model interaction
  */

class World : public IWorld
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

	/**
     * @brief Destructor
	 */
    ~World();

    /**
     * @brief Load saved world from file.
     * @param filepath
     */
    World(std::string filepath);

    /**
     * @brief World generation by given seed.
     * @param rand_seed
     */
    //World(int rand_seed = 0);

    /**
     * @brief World generation by given seed and by specific width/height.
     * @param rand_seed
     * @param width
     * @param height
     */
    World(int rand_seed = 0,
          int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT);

private:
    /// Size of World's region
    const int width;
    const int height;

    //******************************************************************************
    // BASE METHODS.
    //******************************************************************************

public:
	/**
     * @brief Save world to file.
     * @param filepath
	 */
    void save(std::string filepath);

private:

    // TODO: consider if it's necessary to change ObjectHeap to ObjectHeap*
    /// Heap containing all visible World's objects
    ObjectHeap* visible_objs;

    /// Heap containing all hidden World's objects
    ObjectHeap* hidden_objs;

    /// Global world indexator
    Indexator* indexator;

    /// Our world's ObjectFactory
    ObjectFactory* object_factory;

public:

    //******************************************************************************
    // OBJECT HEAP METHODS.
    //******************************************************************************

    void setObjectVisibility(Object *obj, bool visibility);

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Set the value of visible_objs.
     * @param new_var the new value of visible_objs
     */
    //void setAllObjects(ObjectHeap* new_var);

    /**
     * @brief Get the value of visible_objs.
     * @return the value of visible_objs
     */
    //ObjectHeap* getAllObjects();

    //******************************************************************************
    // VIEW METHODS.
    //******************************************************************************

    /**
     * @brief Get objects visible in certain radius around a certain point.
     * @param x x coordinate of screen center
     * @param y y coordinate of screen center
     * @param radius maximal distance from screen center at which object is visible
     * @param size number of ViewObject instances created
     * @return array of ViewObject. Coordinates are relative to (x, y) provided
     *         array is return null-terminated
     */
    Object** getViewObjectsInRange(double x, double y, double radius);

    /**
     * @brief Get weather state at certain coordinates
     * @param x x coordinate of screen center
     * @param y y coordinate of screen center
     * @return ViewWeather - enum indicating weather at specified location
     */
    WeatherType getWeatherAtPoint(double x, double y);

};

#endif // WORLD_H
