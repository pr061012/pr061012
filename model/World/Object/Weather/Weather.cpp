/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Weather.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Weather::Weather(WeatherType type) :
    Object(WEATHER),
    subtype(type)
{

}

Weather::~Weather()
{

}

//******************************************************************************
// WEATHER TYPE.
//******************************************************************************

WeatherType Weather::getSubtype()
{
    return this -> subtype;
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void Weather::setWindow(ObjectHeap* new_var)
{
    this -> window = new_var;
}

ObjectHeap* Weather::getWindow()
{
    return this -> window;
}

