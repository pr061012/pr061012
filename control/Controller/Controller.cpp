/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Controller.h"
#include "../Performer/MovementPerformer.h"

Controller::Controller()
{
}

Controller::Controller(World& world) : world(world)
{
    performers = new Performer[7];
    // TODO
    // Need either indexator pointer or a world's method 'getObjectsInArea'
    // for MovementPerfomer. And also size.
    performers[GO] = (Performer) new MovementPerformer();
}

Controller::~Controller()
{
    delete performers;
}

void Controller:step()
{
    ObjectHeap objects = world.getAllObjects();

    for (i = objects.begin(); i != objects.end(); i++)
    {
        std::vector<Action> * actions = (*i).getActions();
        for (j = actions.begin(); j != actions.end(); j++)
        {
            performers[(*j).getType()].perform(*j);
        }
    }
}