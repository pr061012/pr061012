/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "../Indexator.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Indexator::Window::Window()
{

}

Indexator::Window::~Window()
{

}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void Indexator::Window::setParent(Object * new_var)
{
    this -> parent = new_var;
}

Object * Indexator::Window::getParent()
{
    return this -> parent;
}

void Indexator::Window::setContents(ObjectHeap new_var)
{
    this -> contents = new_var;
}

ObjectHeap Indexator::Window::getContents()
{
    return this -> contents;
}
