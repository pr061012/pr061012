/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "MovementPerformer.h"

// TODO
// Improve movement algo

MovementPerformer::MovementPerformer(const double world_size, 
                                     Indexator& indexator) :
    world_size(world_size), indexator(indexator)
{
}

MovementPerformer::~MovementPerformer()
{
}

void MovementPerformer::perform(Action& action)
{
    Object * actor = action.getActor();
    Point dest = actor -> getCoords() + Point(action.getParam("delta_x"),
                                             action.getParam("delta_y"));

    // Place dest inside world's bounds
    while (dest.getX() < 0)
    {
        dest.setX(dest.getX() + world_size);
    }
    while (dest.getX() >= world_size)
    {
        dest.setX(dest.getX() - world_size);
    }
    while (dest.getY() < 0)
    {
        dest.setY(dest.getY() + world_size);
    }
    while (dest.getY() >= world_size)
    {
        dest.setY(dest.getY() - world_size);
    }

    // Try to place an object and see if it collides with anything
    Shape ghost = actor -> getShape();
    ghost.setCenter(dest);
    ObjectHeap * obstacles = indexator.getAreaContents(ghost);
    if (!obstacles -> getTypeAmount(CREATURE) && 
        !obstacles -> getTypeAmount(BUILDING))
    {
        actor -> setCoords(dest);
        indexator.reindexate(actor);
        action.markAsSucceeded();
    }
    else
    {
        action.markAsFailed();
    }

    // free memory
    delete obstacles;
}
