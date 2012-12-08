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
#include "Indexator/Indexator.h"
#include "../../view/ViewObject/ViewObject.h"
#include "../../common/Math/DoubleComparison.h"

/**
 * @brief Default value for max x and y.
 */
#define DEFAULT_SIZE 5000

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
    virtual ~World();

    /**
     * @brief Load saved world from file.
     * @param filepath
     */
    World(std::string filepath);

    /**
     * @brief World generation by given seed and by specific width/height.
     * @param rand_seed seed of world generation
     * @param size size of side of square of generated world.
     * @param generate_objs     flag indicating whether generate objects or not
     */
    World(int rand_seed = 0, uint size = DEFAULT_SIZE, bool generate_objs = true);

    //**************************************************************************
    // BASE METHODS.
    //**************************************************************************

	/**
     * @brief Save world to file.
     * @param filepath  path to file
	 */
    void save(std::string filepath);

    /**
     * @brief Deletes all objects and generates world one more time
     * @param generate_objs     flag indicating whether generate objects or not
     */
    void reset(uint size = DEFAULT_SIZE, bool generate_objs = true);

private:
    //**************************************************************************
    // CREATING/DELETING WORLD'S ATTRS.
    //**************************************************************************

    /**
     * @brief Clears world and deletes everything.
     */
    void deleteEverything();

    /**
     * @brief Creates all world's attributes.
     */
    void createEverything(bool generate_objs = true);

    //**************************************************************************
    // GENERATION METHODS.
    //**************************************************************************
    
    /**
     * @brief Creates weather somewhere on the map.
     */
    void simulateWeather();

    /**
     * @brief Methods for generating objects of different types.
     */
    void genCreatures();
    void genResources();
    void genWeather();

    /**
     * @brief Generates 2D Perlin noise with fractals.
     * @param x x coordinate.
     * @param y y coordinate.
     * @param power fractal depth.
     * @param seed seed for random number generator.
     * @return noise value.
     */
    double fractalPerlinNoise2D(double x, double y, double power, double seed);

    /**
     * @brief World generating method that uses Perlin's noise.
     */
    void generateWorld();

public:
    /**
     * @brief Generate forest at specific location.
     * @param x_trees maximum amount of trees in X dimension
     * @param y_trees maximum amount of trees in Y dimension
     * @param tree_params ParamArray indicating tree parameters
     * @param prob probability to create tree at this point
     */
    void genForestAt(double x, double y, int x_trees, int y_trees, const ParamArray& tree_params);

    /**
     * @brief Overloading of forementioned function. Generates
     *        trees with default parameters
     */
    void genForestAt(double x, double y);

private:

    /**
     * @brief Generate object at specific location using given position
     *        variance and generation probability.
     * @param point pointat which to create object.
     * @param rand_offset this is the range in which object may be
     *        generated.
     * @param prob probability of tree generation.
     * @param type object type.
     * @param params object parameters.
     * @param no_intersect check that object doesn't intersect any other.
     * @return if object generation succeeded with current probability,
     *         1 is returned. Otherwise, 0 is returned.
     */
    int genObjectAt(Vector point, double rand_offset, double prob,
                  ObjectType type, const ParamArray& params, bool no_intersect = true);

    /**
     * @brief Creates object at given point.
     * @param type type of object
     * @param params the parmeters of object
     * @param no_intersect check that object doesn't intersect any other.
     * @param random_place true if we don't need any current place.
     * @param coords coordinates of an object.
     * @return object pointer if creation was successful, nullptr otherwise.
     */
    Object* createObject(ObjectType type, int subtype, bool no_intersect = false, 
                         bool random_place = true, Vector coords = Vector(0, 0));
    /**
     * @brief Creates object at given point.
     * @param type type of object
     * @param params the parmeters of object
     * @param no_intersect check that object doesn't intersect any other.
     * @param random_place true if we don't need any current place.
     * @param coords coordinates of an object.
     * @return object pointer if creation was successful, nullptr otherwise.
     */
    Object* createObject(ObjectType type, const ParamArray& params, 
                         bool no_intersect = false,
                         bool random_place = true, Vector coords = Vector(0, 0));

public:
    //**************************************************************************
    // OBJECT HEAP METHODS.
    //**************************************************************************

    void setObjectVisibility(Object* obj, bool visibility);

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Set the value of visible_objs
     * @param new_var the new value of visible_objs
     */
    //void setAllObjects(ObjectHeap* new_var);

    /**
     * @brief Add an object to World
     * @param visibility
     * @param obj
     */
    void addObject(bool visibility, Object* obj);

    /**
     * @brief Get World's size
     * @return World's size
     */
    double getSize() const;

    /**
     * @brief Get World's indexator
     * @return World's indexator
     */
    Indexator* getIndexator();

    /**
     * @brief Get World's object factory
     * @return World's object factory
     */
    ObjectFactory* getObjectFactory();

    /**
     * @brief Get the value of visible_objs
     * @return the value of visible_objs
     */
    ObjectHeap* getVisibleObjects();

    /**
     * @brief Get the value of hidden_objs
     * @return the value of hidden_objs
     */
    ObjectHeap* getHiddenObjects();

    /**
     * @brief Get objects in certain radius around (x,y)
     * @param x x coordinate of the range center
     * @param y y coordinate of the range center
     * @param radius range from which objects are returned
     * @return Pointer to ObjectHeap of objects in radius
     *         around (x,y)
     */
    // ObjectHeap* getObjectsInRange(double x, double y, double radius);

    Object* getObjectByID(uint id) const;


    //******************************************************************************
    // VIEW METHODS.
    //******************************************************************************

    /**
     * @brief Get objects visible in square region of certain size at certain vector.
     * @param x x coordinate of screen center
     * @param y y coordinate of screen center
     * @param size maximal distance from screen center at which object is visible
     * @return vector of ViewObject.
     */
    std::vector<const Object*> getViewObjectsInArea(double x, double y, double size) const;

    /**
     * @brief Get weather state at certain coordinates
     * @param x x coordinate of screen center
     * @param y y coordinate of screen center
     * @return ViewWeather - enum indicating weather at specified location
     */
    WeatherType getWeatherAtPoint(double x, double y) const;

private:
    /// Size of World's region
    uint size;

    /// Heap containing all visible World's objects
    ObjectHeap* visible_objs;

    /// Heap containing all hidden World's objects
    ObjectHeap* hidden_objs;

    /// Global world indexator
    Indexator* indexator;

    /// Object creating matrix of parmeters.
    ParamArray ** object_parameters;

    /// Weather probabilities.
    double * weather_probabilities;

    /// Our world's ObjectFactory
    ObjectFactory* object_factory;

    /// Humanoid decision maker.
    const DecisionMaker hum_dmaker;
    /// NonHumanoid decision maker.
    const DecisionMaker nhum_dmaker;

    /**
     * @brief Checks if an object can stand on the point.
     * @param new_obj object to test.
     * @param no_intersect if true, function will check even
     *        if an object is flying or it is solid.
     * @return true, if an object is placed well, false otherwise.
     */
    bool checkCoord(Object* new_obj, bool no_intersect = false );
};

#endif // WORLD_H
