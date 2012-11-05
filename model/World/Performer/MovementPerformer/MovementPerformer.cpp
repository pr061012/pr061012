#include "MovementPerformer.h"

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

    // Try to place an object and see if it collides with anything
    Shape ghost = actor -> getShape();
    ghost.setCenter(dest);
    ObjectHeap * obstacles = indexator.getAreaContents(ghost);
    if (!obstacles -> getTypeAmount(ObjectType(-1)))
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
