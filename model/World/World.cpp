/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "World.h"

#include <iostream>
#include <vector>

#include "../../common/Random/Random.h"

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
}

World::World(int rand_seed, uint size, bool generate_objs) :
    size(size > 0 ? size : DEFAULT_SIZE),
    hum_dmaker(HUMANOID),
    nhum_dmaker(NON_HUMANOID)
{
    srand(rand_seed);

    Log::NOTE(std::string("Creating world with random seed ") +
              std::to_string(rand_seed) + ".");

    this -> createEverything(generate_objs);
}

// Creating resources!
void World::genResources()
{
    ParamArray food_params;
    ParamArray building_mat_params;

    food_params.addKey<ResourceType>("res_type", RES_FOOD);
    food_params.addKey<uint>("res_amount", 10);

    building_mat_params.addKey<ResourceType>("res_type", RES_BUILDING_MAT);
    building_mat_params.addKey<uint>("res_amount", 10);

    uint amount = Random::int_range(3000, 5000);
    for(uint i = 0; i < amount; i++)
    {
        Object* newobj  = object_factory -> createObject(RESOURCE, food_params);

        newobj -> setCoords(Vector(Random::double_range(0, size),
                                   Random::double_range(0, size)));

        Object* grass = object_factory -> createObject(RESOURCE, building_mat_params);

        grass -> setCoords(Vector(Random::double_range(0, size),
                                  Random::double_range(0, size)));

        visible_objs -> push(newobj);
        visible_objs -> push(grass);
    }

    indexator -> reindexate(visible_objs);
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
        new_obj -> setCoords(Vector(Random::double_range(20.0, 70.0),
                                    Random::double_range(20.0, 70.0)));
        visible_objs -> push(new_obj);

        new_obj = object_factory -> createObject(CREATURE, hum_params);
        new_obj -> setCoords(Vector(Random::double_range(20.0, 70.0),
                                    Random::double_range(20.0, 70.0)));
        visible_objs -> push(new_obj);
    }

    indexator -> reindexate(visible_objs);
}

void World::genWeather()
{
    ParamArray weat_params;
    weat_params.addKey<WeatherType>("weat_type", METEOR_SHOWER);
    weat_params.addKey<uint>("weat_steps", 10);

    uint amount = Random::int_range(50, 100);
    for (uint i = 0; i < amount; i++)
    {
        Object* new_obj = object_factory -> createObject(WEATHER, weat_params);

        new_obj -> setCoords(Vector(Random::double_range(0, size),
                                    Random::double_range(0, size)));

        visible_objs -> push(new_obj);
    }

    indexator -> reindexate(visible_objs);
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
