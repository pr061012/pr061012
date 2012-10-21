/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Weather.h"

//**************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//**************************************************************************

Weather::Weather()
{

}

Weather::~Weather()
{

}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void setSubtype(WeatherType new_var)
{
    this -> subtype = new_var;
}


WeatherType getSubtype()
{
    return subtype;
}

void setWindow(ObjectHeap * new_var)
{
    this -> window = new_var;
}


ObjectHeap * getWindow()
{
    return window;
}


void setViewArea(Frame new_var)
{
    this -> view_area = new_var;
}


Frame getViewArea()
{
    return view_area;
}
