/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "World.h"

#include <iostream>
#include <vector>

#include "../BasicFuncs.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

World::~World()
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

World::World(std::string filepath) :
    size(DEFAULT_SIZE),
    hum_dmaker(HUMANOID),
    nhum_dmaker(NON_HUMANOID)
{

}

World::World(int rand_seed, int size) :
    size(size > 0 ? size : DEFAULT_SIZE),
    hum_dmaker(HUMANOID),
    nhum_dmaker(NON_HUMANOID)
{
    srand(rand_seed);

    std::cout << "Creating world with rand_seed="
              << rand_seed << std::endl;

    object_factory = new ObjectFactory(hum_dmaker, nhum_dmaker);
    visible_objs = new ObjectHeap();


    indexator = new Indexator((double)this->size);

    hidden_objs = new ObjectHeap();

    ParamArray params;

    params.addKey("res_type", WOOD);
    params.addKey("res_amount", 10);

    for(int i = 3000 + rand()%5000; i>=0; --i)
    {
        Object* newobj  = object_factory -> createObject(RESOURCE, params);

        // TODO: Do something with these magic consts.
        newobj -> setCoords(Point(randFromRange(0, size),
                                  randFromRange(0, size)));

        visible_objs -> push(newobj);
        indexator -> reindexate(newobj);

//        std::cout << "Created resource at x = "
//                  << newobj->getCoords().getX() << ", y = "
//                  << newobj->getCoords().getY()
//                  << " with collision model as circle rad = 50"
//                  << std::endl;
    }

    // Creating cows!
    ParamArray nhum_params;
    nhum_params.addKey<CreatureType>("creat_type", NON_HUMANOID);

    uint amount = 10 + rand() % 10;
    for (uint i = 0; i < amount; i++)
    {
        Object* new_obj = object_factory -> createObject(CREATURE, nhum_params);

        // TODO: Do something with these magic consts.
        new_obj -> setCoords(Point(randFromRange(20.0, 70.0),
                                   randFromRange(20.0, 70.0)));

        visible_objs -> push(new_obj);
        indexator -> reindexate(new_obj);
    }
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

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void World::addObject(bool visibility, Object *obj)
{
    if (visibility)
    {
        this -> visible_objs -> push(obj);
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

std::vector<Object*>* World::getViewObjectsInRange(double x, double y, double radius) const
{
    Point center(x, y);
    Shape area(center, CIRCLE, radius*2);
    ObjectHeap* objects = indexator->getAreaContents(area);
    ObjectHeap::const_iterator it = objects->begin();

    std::vector<Object*>* retval = new std::vector<Object*>;

    for (; it != objects -> end(); it++)
    {
        retval -> push_back(*it);
    }

    delete objects;

    return retval;
}

WeatherType World::getWeatherAtPoint(double x, double y) const
{
    // TODO: Cycle through weather objects
    // and return the closest type of weather for this area.
    return RAIN;
}
