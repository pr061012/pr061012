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
    delete visible_objs;
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

    std::cout << "Creating world with rand_seed="
              << rand_seed << std::endl;

    object_factory = new ObjectFactory();
    visible_objs = new ObjectHeap();

    indexator = new Indexator((double)width);

    ParamArray params;

    params.addKey("res_type", WOOD);
    params.addKey("res_amount", 10);

    for(int i = 30 + rand()%50; i>=0; --i)
    {
        Object* newobj  = object_factory->createObject(RESOURCE, params);
        newobj->setCoords(Point(20.0+rand()%50,20.0+rand()%50));
        newobj->setShape(Shape(newobj->getCoords(), CIRCLE, 10.0));
        visible_objs->push(newobj);

        indexator->reindexate(newobj);

//        std::cout << "Created resource at x = "
//                  << newobj->getCoords().getX() << ", y = "
//                  << newobj->getCoords().getY()
//                  << " with collision model as circle rad = 50"
//                  << std::endl;
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

//void World::setAllObjects(ObjectHeap* new_var)
//{
//    this -> visible_objs = new_var;
//}

//ObjectHeap* World::getAllObjects()
//{
//    return this -> visible_objs;
//}

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

//******************************************************************************
// VIEW METHODS.
//******************************************************************************

Object** World::getViewObjectsInRange(double x, double y, double radius)
{
    Object** retval;

    Point center(x, y);
    Shape area(center, CIRCLE, radius*2);
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
