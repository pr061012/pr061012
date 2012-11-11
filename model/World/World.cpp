/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "World.h"

#include <iostream>

#include "../BasicFuncs.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

World::~World()
{    
    delete object_factory;
    delete indexator;
    delete visible_objs;
    delete hidden_objs;
}

World::World(std::string filepath) :
    size(DEFAULT_SIZE)
{

}

World::World(int rand_seed, int size) :
    size(size > 0 ? size : DEFAULT_SIZE)
{
    srand(rand_seed);

    std::cout << "Creating world with rand_seed="
              << rand_seed << std::endl;

    object_factory = new ObjectFactory(DecisionMaker(HUMANOID),
                                       DecisionMaker(NON_HUMANOID));
    visible_objs = new ObjectHeap();


    indexator = new Indexator((double)this->size);

    hidden_objs = new ObjectHeap();

    ParamArray params;

    params.addKey("res_type", WOOD);
    params.addKey("res_amount", 10);

    for(int i = 30 + rand()%50; i>=0; --i)
    {
        Object* newobj  = object_factory -> createObject(RESOURCE, params);

        // TODO: Do something with these magic consts.
        newobj -> setCoords(Point(randFromRange(20.0, 70.0),
                                  randFromRange(20.0, 70.0)));

        newobj -> setShapeType(CIRCLE);
        newobj -> setShapeSize(10.0);
        visible_objs -> push(newobj);

        indexator -> reindexate(newobj);

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

double World::getSize()
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

//ObjectHeap *World::getObjectsInRange(double x, double y, double radius)
//{
//    Point center(x, y);
//    Shape area(center, CIRCLE, radius*2);
//    ObjectHeap* ret = indexator->getAreaContents(area);
//    return ret;
//}

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

    int size = objects -> getAmount();

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
