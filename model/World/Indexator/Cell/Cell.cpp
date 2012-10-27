#include "../Indexator.h"

//******************************************************************************
// CONSTRUCTOR / DESTRUCTOR
//******************************************************************************

Indexator::Cell::Cell()
{
}

Indexator::Cell::Cell(Shape area)
{
    this -> area = area;
}

Indexator::Cell::~Cell()
{
}

//******************************************************************************
// ACCESSORS
//******************************************************************************

Shape Indexator::Cell::getArea()
{
    return area;
}

void Indexator::Cell::setArea(Shape area)
{
    this -> area = area;
}

Indexator::Cell * Indexator::Cell::getNeighbours()
{
    Cell * result = new Cell[4];
    for (int i = 0; i < 4; i++)
    {
        result[i] = Cell(neighbours[i]);
    }
    return result;
}

void Indexator::Cell::setNeighbours(Indexator::Cell * neighbours)
{
    for (int i = 0; i < 4; i++)
    {
        this -> neighbours[i] = neighbours[i];
    }
}

ObjectHeap * Indexator::Cell::getObjects()
{
    return &objects;
}

//******************************************************************************
// OTHER
//******************************************************************************

void Indexator::Cell::step()
{
}

void Indexator::Cell::checkObject(Object * object)
{
}
