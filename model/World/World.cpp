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
    // TODO: add a check for positive arguments
    this->width  = width;
    this->height = height;

    // For now, just generate a group of humans in a row.

    std::map <std::string, void*> params;
    int pos[] = {0, 0};

    params["x"] = &pos[0];
    params["y"] = &pos[1];

    createObject(HUMANOID, params);

    pos[0] = 10;
    createObject(HUMANOID, params);

    pos[0] = 20;
    createObject(HUMANOID, params);
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
