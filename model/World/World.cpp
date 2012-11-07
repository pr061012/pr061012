/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "World.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

World::~World()
{    
    delete object_factory;
    delete indexator;
}

World::World(std::string filepath) :
    width(DEFAULT_WIDTH),
    height(DEFAULT_HEIGHT)
{

}

World::World(int rand_seed) :
    width(DEFAULT_WIDTH),
    height(DEFAULT_HEIGHT)
{
    srand(rand_seed);
   // World(rand_seed, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

World::World(int rand_seed, int width, int height) :
    width(width  > 0 ? width  : DEFAULT_WIDTH),
    height(height > 0 ? height : DEFAULT_HEIGHT)
{
    srand(rand_seed);

    //this->width  = width  > 0 ? width  : DEFAULT_WIDTH;
    //this->height = height > 0 ? height : DEFAULT_HEIGHT;

    object_factory = new ObjectFactory();

    // FIXME: No such constructor for indexator?
    indexator = new Indexator();

    // For now, just generating a group of humans in a row.

    std::map <std::string, void*> params;
    int pos[] = {0, 0};

    params["x"] = &pos[0];
    params["y"] = &pos[1];

    // object_factory->createObject(HUMANOID, params);

    // pos[0] = 10;
    // object_factory->createObject(HUMANOID, params);

    // pos[0] = 20;
    // object_factory->createObject(HUMANOID, params);
}

void World::addGodAction(Action *action)
{
}

//******************************************************************************
// BASE METHODS.
//******************************************************************************

void World::step()
{
    // TODO: Prepare the queue of actions for controller.
}

void World::save(std::string filepath)
{
    // TODO: Create file at filepath and save it (format?)
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

Object** World::getViewObjectsInRange(double x, double y, double radius)
{
    // Check all_objects in certain range and create array
    // of (tiny) objects containing neccessary parameters.
    return NULL;
}

WeatherType World::getWeatherAtPoint(double x, double y)
{
    // TODO: Cycle through weather objects
    // and return the closest type of weather for this area.
    return RAIN;
}
