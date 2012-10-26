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

}

World::World(int rand_seed)
{

}

World::World(std::string filepath)
{

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
        object->
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
