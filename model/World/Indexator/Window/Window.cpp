/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Window.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Window::Window()
{

}

Window::~Window()
{

}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void Window::setParent(Object * new_var)
{
    this -> parent = new_var;
}

Object * Window::getParent()
{
    return this -> parent;
}

void Window::setContents(ObjectHeap new_var)
{
    this -> contents = new_var;
}

ObjectHeap Window::getContents()
{
    return this -> contents;
}
