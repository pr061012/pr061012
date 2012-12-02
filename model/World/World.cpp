/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "World.h"

#include <iostream>
#include <vector>

#include "../../common/BasicDefines.h"
#include "../../common/Math/Random.h"
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

    this -> createEverything(generate_objs);
}

//******************************************************************************
// GENERATION METHODS.
//******************************************************************************

// Creating resources!
void World::genResources()
{
    ParamArray food_params;
    ParamArray building_mat_params;

    food_params.addKey<ResourceType>("res_type", RES_FOOD);

    building_mat_params.addKey<ResourceType>("res_type", RES_BUILDING_MAT);

    uint amount = Random::int_range(30, 50);
    for(uint i = 0; i < amount; i++)
    {
        Object* newobj  = object_factory -> createObject(RESOURCE, food_params);

        newobj -> setCoords(Vector(Random::double_range(0, size),
                                   Random::double_range(0, size)));

        Object* grass = object_factory -> createObject(RESOURCE, building_mat_params);

        grass -> setCoords(Vector(Random::double_range(0, size),
                                  Random::double_range(0, size)));

        if (checkCoord(newobj))
        {
            indexator -> addObject(newobj);
            visible_objs -> push(newobj);
        }
        else
        {
            delete newobj;
        }

        if (checkCoord(grass))
        {
            indexator -> addObject(grass);
            visible_objs -> push(grass);
        }
        else
        {
            delete grass;
        }
    }
}

// Creating cows!
void World::genCreatures()
{
    ParamArray nhum_params;
    nhum_params.addKey<CreatureType>("creat_type", NON_HUMANOID);

    ParamArray hum_params;
    hum_params.addKey<CreatureType>("creat_type", HUMANOID);

    uint amount = Random::int_range(10, 20);
    for (uint i = 0; i < amount; i++)
    {
        Object* new_obj = object_factory -> createObject(CREATURE, nhum_params);
        new_obj -> setCoords(Vector(Random::double_range(size / 3, 2 * size / 3),
                                    Random::double_range(size / 3, 2 * size / 3)));

        if (checkCoord(new_obj))
        {
            indexator -> addObject(new_obj);
            visible_objs -> push(new_obj);
        }
        else
        {
            delete new_obj;
        }
        new_obj = object_factory -> createObject(CREATURE, hum_params);
        new_obj -> setCoords(Vector(Random::double_range(size / 3, 2 * size / 3),
                                    Random::double_range(size / 3, 2 * size / 3)));

        if (checkCoord(new_obj))
        {
            indexator -> addObject(new_obj);
            visible_objs -> push(new_obj);
        }
        else
        {
            delete new_obj;
        }
    }
}

void World::genWeather()
{
    ParamArray weat_params;
    weat_params.addKey<WeatherType>("weat_type", METEOR_SHOWER);

    uint amount = Random::int_range(5, 10);
    for (uint i = 0; i < amount; i++)
    {
        Object* new_obj = object_factory -> createObject(WEATHER, weat_params);

        new_obj -> setCoords(Vector(Random::double_range(0, size),
                                    Random::double_range(0, size)));

        visible_objs -> push(new_obj);

    }

    indexator -> reindexate(visible_objs);
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
            genTreeAt(x + (i-x_center)*interval, y + (j-y_center)*interval, shift, probs[i][j], tree_params);
        }
    }

}

void World::genForestAt(double x, double y)
{
    ParamArray tree_params;
    tree_params.addKey<ResourceType>("res_type", RES_BUILDING_MAT);
    tree_params.addKey<uint>("res_amount", 10);

    this -> genForestAt(x, y, 20, 20, tree_params);

}

void World::genTreeAt(double x, double y, const ParamArray& tree_params)
{
    Object* new_obj = object_factory -> createObject(RESOURCE, tree_params);

    new_obj -> setCoords(Vector(x, y));
    if (checkCoord(new_obj))
    {
        indexator -> addObject(new_obj);
        visible_objs -> push(new_obj);
    }
    else
    {
        delete new_obj;
    }
}

int World::genTreeAt(double x, double y, double rand_offset, double prob, const ParamArray &tree_params)
{
    if( DoubleComparison::isGreater(prob, Random::double_num(1.0)) )
    {
        double x_rand = Random::double_num(2*rand_offset) - rand_offset;
        double y_rand = Random::double_num(2*rand_offset) - rand_offset;

        this -> genTreeAt(x + x_rand, y + y_rand, tree_params);

        return 0;
    }
    return 1;
}

//******************************************************************************
// BASE METHODS.
//******************************************************************************

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
        genCreatures();
        genResources();
        genWeather();
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

Object *World::getObjectByID(uint id)
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

bool World::checkCoord(Object *new_obj)
{
    bool ret = false;

    Shape shape = new_obj -> getShape();
    // Get obstacles
    ObjectHeap obstacles = indexator -> getAreaContents(shape, new_obj);

    uint count_creature = obstacles.getTypeAmount(CREATURE);
    uint count_resource = obstacles.getTypeAmount(RESOURCE);

    if
    (
        !count_creature &&
        !count_resource
    )
    {
        ret = true;
    }


    return ret;
}
