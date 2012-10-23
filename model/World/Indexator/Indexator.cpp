#include "Indexator.h"

//******************************************************************************
// CONSTRUCTORS/DESTRUCTOR.
//******************************************************************************

Indexator::Indexator()
{
}

Indexator::Indexator(ObjectHeap *list)
{

}

Indexator::~Indexator()
{

}

//******************************************************************************
// GETTING OBJECTS.
//******************************************************************************

ObjectHeap * Indexator::getFrameContents(Frame frame)
{

}

ObjectHeap * Indexator::createWindow(Object * object)
{

}

//******************************************************************************
// STEP.
//******************************************************************************

void Indexator::step()
{

}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void Indexator::setWindows(std::vector <Window> new_var)
{
    this -> windows = new_var;
}

std::vector <Window> Indexator::getWindows()
{
    return this -> windows;
}
