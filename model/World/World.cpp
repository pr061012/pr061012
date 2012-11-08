/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "World.h"

#include <iostream>

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

World::~World()
{    
    delete object_factory;
    delete indexator;
    delete all_objects;
}

World::World(std::string filepath) :
    width(DEFAULT_WIDTH),
    height(DEFAULT_HEIGHT)
{

}

//World::World(int rand_seed) :
//    width(DEFAULT_WIDTH),
//    height(DEFAULT_HEIGHT)
//{
//    srand(rand_seed);
//}

World::World(int rand_seed, int width, int height) :
    width(width  > 0 ? width  : DEFAULT_WIDTH),
    height(height > 0 ? height : DEFAULT_HEIGHT)
{
    srand(rand_seed);

    //this->width  = width  > 0 ? width  : DEFAULT_WIDTH;
    //this->height = height > 0 ? height : DEFAULT_HEIGHT;

    object_factory = new ObjectFactory();
    all_objects = new ObjectHeap();

    indexator = new Indexator((double)width);

    // For now, just generating a group of humans in a row.

    ParamArray params;

//    params.addKey("x", 0);
//    params.addKey("y", 0);
    params.addKey("res_type", WOOD);
    params.addKey("res_amount", 10);
    //params.addKey("creat_type", HUMANOID);
//    params.addKey("creat_type", HUMANOID);

    Object* newobj  = object_factory->createObject(RESOURCE, params);
    newobj->setCoords(Point(0,0));
    newobj->setShape(Shape(newobj->getCoords(), CIRCLE, 50.0));
    all_objects->push(newobj);

    indexator->reindexate(newobj);

    std::cout << "Created resource at x = "
              << newobj->getCoords().getX() << ", y = "
              << newobj->getCoords().getY()
              << " with collision model as circle rad = 50"
              << std::endl;

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

void World::setAllObjects(ObjectHeap* new_var)
{
    this -> all_objects = new_var;
}

ObjectHeap* World::getAllObjects()
{
    return this -> all_objects;
}

//******************************************************************************
// VIEW METHODS.
//******************************************************************************

Object** World::getViewObjectsInRange(double x, double y, double radius)
{
    Object** retval;

    Point center(x, y);
    Shape area(center, CIRCLE, radius);
    ObjectHeap* objects = indexator->getAreaContents(area);
    ObjectHeap::const_iterator it = objects->begin();

    int size = objects->getAmount();

    retval = new Object*[size + 1];

    for(int i = 0; i<size; ++i)
    {
        retval[i] = it[i];
    }
    retval[size] = NULL;

//    std::cout << "Returning objects array size="
//              << size << std::endl;

    delete objects;

    return retval;
}

WeatherType World::getWeatherAtPoint(double x, double y)
{
    // TODO: Cycle through weather objects
    // and return the closest type of weather for this area.
    return RAIN;
}
