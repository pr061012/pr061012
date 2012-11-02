#include "Indexator.h"
#include <cmath>

const double Indexator::MAX_CELL_SIZE = 100;

//******************************************************************************
// CONSTRUCTORS/DESTRUCTOR.
//******************************************************************************

Indexator::Indexator()
{
}

Indexator::Indexator(double size, ObjectHeap *list)
{
    row_size = ceil(size/MAX_CELL_SIZE);
    cell_size = size / row_size;
    cells = new ObjectHeap*[row_size];

    for (int i = 0; i< row_size; i++)
    {
        cells[i] = new ObjectHeap[row_size];
    }

    if (list)
    {
        reindexate(list);
    }
}

Indexator::~Indexator()
{

}

//******************************************************************************
// GETTING OBJECTS.
//******************************************************************************

Indexator::ObjectHeap * Indexator::getAreaContents(Shape area)
{
    return 0;
}

//******************************************************************************
// REINDEXATE.
//******************************************************************************

void Indexator::reindexate(ObjectHeap * objects)
{
    ObjectHeap::iterator i;

    for (i = objects -> begin(); i != objects -> end(); i++)
    {
        reindexate(*i);
    }

}

void Indexator::reindexate(Object * object)
{
    Shape shape = object -> getShape();
    Point rt = shape.getRightTop();
    Point lb = shape.getLeftBottom();
    Area  area;
    area[0] = ceil(lb.getX() / cell_size);
    area[1] = ceil(lb.getY() / cell_size);
    area[2] = ceil(rt.getX() / cell_size);
    area[3] = ceil(rt.getY() / cell_size);

    // Check if an object exists in our index
    Index::iterator i = index.find(object);
    if (i == index.end())
    {
        //index[object] = area;
        return;
    }

    Area &old_area = i -> second;
}
