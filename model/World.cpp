/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/


#include "World.h"

#include <iostream>
#include <vector>

#include "../common/BasicDefines.h"
#include "../common/Math/Random.h"
#include "Object/Creatures/Creature.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

World::~World()
{
    this -> deleteEverything();
}

World::World(std::string filepath) :
    size(DEFAULT_SIZE),
    hum_dmaker(HUMANOID),
    nhum_dmaker(NON_HUMANOID)
{
    Creature::world_size = size;
}

World::World(int rand_seed, uint size, bool generate_objs) :
    size(size > 0 ? size : DEFAULT_SIZE),
    hum_dmaker(HUMANOID),
    nhum_dmaker(NON_HUMANOID)
{
    srand(rand_seed);

    Log::NOTE(std::string("Creating world with random seed ") +
              std::to_string(rand_seed) + ".");

    Creature::world_size = size;
    
    // Initialize object parameters
    object_parameters = new ParamArray*[AMNT_OBJECT_TYPES];
    
    // Resources
    object_parameters[RESOURCE] = new ParamArray[AMNT_RESOURCE_TYPES];
    object_parameters[RESOURCE][GRASS].addKey<ResourceType>("res_type", GRASS);
    object_parameters[RESOURCE][TREE].addKey<ResourceType>("res_type", TREE);
    object_parameters[RESOURCE][MEAT].addKey<ResourceType>("res_type", MEAT);
    object_parameters[RESOURCE][WATER].addKey<ResourceType>("res_type", WATER);
    object_parameters[RESOURCE][BERRIES].addKey<ResourceType>("res_type", BERRIES);
    // Creatures
    object_parameters[CREATURE] = new ParamArray[AMNT_NONHUMANOID_TYPES + 1];
    object_parameters[CREATURE][AMNT_NONHUMANOID_TYPES].
                                addKey<CreatureType>("creat_type", HUMANOID);
    object_parameters[CREATURE][COW].addKey<CreatureType>("creat_type", NON_HUMANOID);
    object_parameters[CREATURE][COW].addKey<NonHumanoidType>("nhum_type", COW);

    object_parameters[CREATURE][DRAGON].addKey<CreatureType>("creat_type", NON_HUMANOID);
    object_parameters[CREATURE][DRAGON].addKey<NonHumanoidType>("nhum_type", DRAGON);
    
    // Weather
    object_parameters[WEATHER] = new ParamArray[AMNT_WEATHER_TYPES];
    object_parameters[WEATHER][METEOR_SHOWER].
                        addKey<WeatherType>("weat_type", METEOR_SHOWER);
    object_parameters[WEATHER][RAIN].
                        addKey<WeatherType>("weat_type", RAIN);
    object_parameters[WEATHER][CLOUDS].
                        addKey<WeatherType>("weat_type", CLOUDS);
    object_parameters[WEATHER][HURRICANE].
                        addKey<WeatherType>("weat_type", HURRICANE);

    // Weather probabilities
    weather_probabilities = new double[AMNT_WEATHER_TYPES];
    weather_probabilities[RAIN]          = GEN_WEAT_RAIN_PROBABILITY;
    weather_probabilities[CLOUDS]        = GEN_WEAT_CLOUDS_PROBABILITY;
    weather_probabilities[METEOR_SHOWER] = GEN_WEAT_METEOR_SHOWER_PROBABILITY;
    weather_probabilities[HURRICANE]     = GEN_WEAT_HURRICANE_PROBABILITY;

    this -> createEverything(generate_objs);
}

//******************************************************************************
// GENERATION METHODS.
//******************************************************************************

// Creating resources!
void World::genResources()
{
    uint amount = Random::int_range(30, 50);
    for(uint i = 0; i < amount; i++)
    {
        createObject(RESOURCE, GRASS);
        createObject(RESOURCE, TREE);
    }
}

// Creating cows!
void World::genCreatures()
{
    for (uint k = 0; k <= AMNT_NONHUMANOID_TYPES; k++)
    {
        uint amount;
        if (k == COW) amount = Random::int_range(20, 30);
        else if (k == DRAGON) amount = Random::int_range(1, 3);
        // humans
        else if (k == AMNT_NONHUMANOID_TYPES) amount = Random::int_range(10, 20);
        else amount = 0;

        for (uint i = 0; i < amount; i++)
        {
            Object* new_obj = createObject(CREATURE, k);
        }
    }
}

// Create weather somewhere on the map depending on probability.
void World::simulateWeather()
{
    double dice = Random::double_num(1.0);
    double prob = 0;
    for (int i = 0; i < AMNT_WEATHER_TYPES; i++)
    {
        prob += weather_probabilities[i];
        if (dice < prob)
        {
            createObject(WEATHER, i);
            return;
        }
    }
}

// Create creatures.
void World::simulateCreatures()
{
    for (uint i = 0; i < GEN_RECREATE_AMOUNT_COWS; i++)
    {
        createObject(CREATURE, COW);
    }
    for (uint i = 0; i < GEN_RECREATE_AMOUNT_HUMANS; i++)
    {
        createObject(CREATURE, AMNT_NONHUMANOID_TYPES);
    }
}

// Create resources.
void World::simulateResources()
{
    for (uint i = 0; i < GEN_RECREATE_AMOUNT_TREE; i++)
    {
        createObject(RESOURCE, TREE);
    }
    for (uint i = 0; i < GEN_RECREATE_AMOUNT_GRASS; i++)
    {
        createObject(RESOURCE, GRASS);
    }
}

void World::genWeather()
{
    uint amount = Random::int_range(GEN_WEAT_START_COUNT_MIN, GEN_WEAT_START_COUNT_MAX);
    for (uint i = 0; i < amount; i++)
    {
        simulateWeather();
    }
}



void World::genForestAt(double x, double y, int x_trees, int y_trees, const ParamArray& tree_params)
{
    const double interval = GEN_TREE_INTERVAL;
    const double shift    = interval/3;

    // x_trees and y_trees have to be odd values
    if(x_trees%2 == 0)x_trees++;
    if(y_trees%2 == 0)y_trees++;

    // Probabilities of tree generation at certain coordinates
    double probs[x_trees][y_trees];

    int x_center = x_trees/2 + 1;
    int y_center = y_trees/2 + 1;

    // Calculating probabilities of tree generation based on distance
    for(int i = 0; i < x_center; ++i)
    {
        for(int j = 0; j < y_center; ++j)
        {
            double distance = sqrt( pow(x_center - i, 2) + pow(y_center - j, 2) );
            probs[i][j] = probs[x_trees - i - 1][y_trees - j - 1] = probs[i][y_trees - j - 1] = probs[x_trees - i - 1][j] = 1.0 - distance*GEN_TREE_PROB_DECAY;
        }
    }

    // Generating trees.
    for(int i = 0; i < x_trees; ++i)
    {
        for(int j = 0; j < y_trees; ++j)
        {
            genObjectAt(Vector(x + (i-x_center)*interval, y + (j-y_center)*interval),
                      shift, probs[i][j], RESOURCE, tree_params);
        }
    }

}

void World::genForestAt(double x, double y)
{
    ParamArray tree_params;
    tree_params.addKey<ResourceType>("res_type", TREE);
    tree_params.addKey<uint>("res_amount", 10);

    this -> genForestAt(x, y, 20, 20, tree_params);

}

int World::genObjectAt(Vector point, double rand_offset, double prob,
                        ObjectType type, const ParamArray &params, bool no_intersect)
{
    if( DoubleComparison::isGreater(prob, Random::double_num(1.0)) )
    {
        Vector offset(Random::double_num(2*rand_offset) - rand_offset,
                      Random::double_num(2*rand_offset) - rand_offset);

        if (createObject(type, params, no_intersect, false, point + offset)
            != nullptr)
        {
            return 1;
        }
    }
    return 0;
}

//******************************************************************************
// BASE METHODS.
//******************************************************************************

Object* World::createObject(ObjectType type, int subtype, bool no_intersect,
                         bool random_place, Vector coords)
{
    return createObject(type, object_parameters[type][subtype], no_intersect,
                        random_place, coords);
}

// Tries to create object with given parameters.
Object* World::createObject(ObjectType type, const ParamArray& params, bool no_intersect,
                         bool random_place, Vector coords)
{ 
    bool success = false;
    Object* new_obj = object_factory -> createObject(type, params);
    double obj_size = new_obj -> getShape().getSize() / 2;

    // If object can have any coords, try to place them until success.
    do
    {
        if (random_place)
        {
            coords = Vector(Random::double_range(obj_size, size - obj_size),
                            Random::double_range(obj_size, size - obj_size));
        }

        new_obj -> setCoords(coords);
        if (checkCoord(new_obj, no_intersect))
        {
            addObject(true, new_obj);
            success = true;
        }
    } 
    while (!success && random_place);

    if (!success)
    {
        delete new_obj;
        return nullptr;
    }
    else
    {
        if (type == CREATURE)
        {
            Object* drop = object_factory -> 
                            createObject(RESOURCE, object_parameters[RESOURCE][MEAT]);
            this -> addObject(false, drop);
            dynamic_cast<Creature*>(new_obj) -> getDropObjects() -> push(drop);
        }
        return new_obj;
    }
}

void World::setObjectVisibility(Object *obj, bool visibility)
{
    // visible_objs->hasObject(obj);
}

void World::save(std::string filepath)
{
    // TODO: Create file at filepath and save it (format?)
}

void World::reset(uint size, bool generate_objs)
{
    this -> size = size > 0 ? size : DEFAULT_SIZE;
    Creature::world_size = size;
    this -> deleteEverything();
    this -> createEverything(generate_objs);
}

void World::deleteEverything()
{
    // Deleting factory and indexator.
    delete object_factory;
    delete indexator;

    // Deleting visible objects.
    ObjectHeap::iterator iter;
    for(iter = visible_objs -> begin(); iter != visible_objs -> end(); iter++)
    {
        delete *iter;
    }
    delete visible_objs;

    // Deleting hidden objects.
    for(iter = hidden_objs -> begin(); iter != hidden_objs -> end(); iter++)
    {
        delete *iter;
    }
    delete hidden_objs;
}

void World::createEverything(bool generate_objs)
{
    object_factory = new ObjectFactory(hum_dmaker, nhum_dmaker);

    visible_objs = new ObjectHeap();
    hidden_objs  = new ObjectHeap();

    indexator = new Indexator((double) this -> size);

    if (generate_objs)
    {
        /*
        genCreatures();
        genResources();
        genWeather();
        */
        generateWorld();
    }
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void World::addObject(bool visibility, Object *obj)
{
    if (visibility)
    {
        this -> visible_objs -> push(obj);
        this -> indexator -> reindexate(obj);
    }
    else
    {
        this -> hidden_objs -> push(obj);
    }
}

ObjectFactory* World::getObjectFactory()
{
    return this -> object_factory;
}

double World::getSize() const
{
    return this -> size;
}

Indexator* World::getIndexator()
{
    return this -> indexator;
}

ObjectHeap* World::getVisibleObjects()
{
    return this -> visible_objs;
}

ObjectHeap* World::getHiddenObjects()
{
    return this -> hidden_objs;
}

//******************************************************************************
// VIEW METHODS.
//******************************************************************************

std::vector<const Object*> World::getViewObjectsInArea(double x, double y, double size) const
{
    Vector center(x, y);
    Shape area(center, CIRCLE, size*2);
    ObjectHeap objects = indexator->getAreaContents(area);
    ObjectHeap::const_iterator it;

    std::vector<const Object*> retval;

    for (it = objects.begin(); it != objects.end(); it++)
    {
        retval.push_back(*it);
    }

    return retval;
}

WeatherType World::getWeatherAtPoint(double x, double y) const
{
    // TODO: Cycle through weather objects
    // and return the closest type of weather for this area.
    return RAIN;
}

Object *World::getObjectByID(uint id) const
{
    ObjectHeap::const_iterator it;

    for (it = visible_objs -> begin(); it != visible_objs -> end(); it++)
    {
        if((*it) -> getObjectID() == id) return *it;
    }

    for (it = hidden_objs -> begin(); it != hidden_objs -> end(); it++)
    {
        if((*it) -> getObjectID() == id) return *it;
    }

    return NULL;
}

bool World::checkCoord(Object *new_obj, bool no_intersect)
{
    if ((!new_obj -> isSolid() || new_obj -> isCurrentlyFlying()) &&
        !no_intersect)
    {
        return true;
    }

    Shape shape = new_obj -> getShape();
    ObjectHeap obstacles = indexator -> getAreaContents(shape, new_obj);

    if (no_intersect)
    {
        if (!obstacles.getAmount() - obstacles.getTypeAmount(WEATHER))
        {
            return true;
        }
    }
    else
    {
        for (ObjectHeap::iterator i = obstacles.begin();
             i != obstacles.end(); i++)
        {
            if ((*i) -> isSolid() && !(*i) -> isCurrentlyFlying())
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
