/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "World.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

World::World()
{
    World(0);
}

World::~World()
{    
    delete object_factory;
    delete indexator;
}

World::World(std::string filepath)
{

}

World::World(int rand_seed)
{
    World(rand_seed, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

World::World(int rand_seed, int width, int height)
{
    srand(rand_seed);

    this->width  = width  > 0 ? width  : DEFAULT_WIDTH;
    this->height = height > 0 ? height : DEFAULT_HEIGHT;

    object_factory = new ObjectFactory(&all_objects);
    indexator = new Indexator(all_objects);

    // For now, just generate a group of humans in a row.

    std::map <std::string, void*> params;
    int pos[] = {0, 0};

    params["x"] = &pos[0];
    params["y"] = &pos[1];

    object_factory->createObject(HUMANOID, params);

    pos[0] = 10;
    object_factory->createObject(HUMANOID, params);

    pos[0] = 20;
    object_factory->createObject(HUMANOID, params);
}

//******************************************************************************
// BASE METHODS.
//******************************************************************************

void World::step()
{
    Object* object;

    all_objects.cleanPosition();

    // Initiate descending update of world objects contained in all_objects
    while(object = all_objects.next())
    {
        object->step();
    }
}

void World::save(std::string filepath)
{

}


//******************************************************************************
// ACCESSORS.
//******************************************************************************

void World::setAllObjects(ObjectHeap new_var)
{
    this -> all_objects = new_var;
}

ObjectHeap World::getAllObjects()
{
    return this -> all_objects;
}

//******************************************************************************
// VIEW METHODS.
//******************************************************************************

ViewObject **World::getViewObjectsInRange(double x, double y, double radius)
{
}

ViewWeather World::getWeatherAtPoint(double x, double y)
{
}
