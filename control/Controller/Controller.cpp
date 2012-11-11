/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Controller.h"
#include "../Performer/MovementPerformer/MovementPerformer.h"

Controller::Controller(World& world) :
    world(world)
{
    // TODO
    // Need either indexator pointer or a world's method 'getObjectsInArea'
    // for MovementPerfomer. And also size.
    performers[GO] = (Performer *) new MovementPerformer();
}

Controller::~Controller()
{
    delete performers;
}

void Controller::step()
{
    ObjectHeap * objects = world.getAllObjects();

    for (ObjectHeap::iterator i = objects -> begin(); i != objects -> end(); i++)
    {
        std::vector<Action> * actions = (*i) -> getActions();
        for (std::vector<Action>::iterator j = actions -> begin(); 
                    j != actions -> end(); j++)
        {
            performers[(*j).getType()] -> perform(*j);
        }
    }
}
