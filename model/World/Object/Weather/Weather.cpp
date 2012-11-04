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
    subtype(type),
    covered_objs(new ObjectHeap)
{
}

Weather::~Weather()
{
    delete covered_objs;
}

//******************************************************************************
// WEATHER ACTIONS.
//******************************************************************************

std::vector <Action> * Object::getActions()
{
    // TODO: Add actions generation.

    return &(this -> actions);
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

ObjectHeap * Weather::getCoveredObjects()
{
    return this -> covered_objs;
}
