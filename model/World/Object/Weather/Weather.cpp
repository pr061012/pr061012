/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Weather.h"

#include "../../../BasicFunc.h"
#include "../../../BasicDefines.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Weather::Weather(WeatherType type) :
    Object(WEATHER),
    subtype(type),
    covered_objs(new ObjectHeap)
{
    this -> steps = randFromRange(WEAT_STEPS_MIN, WEAT_STEPS_MAX);
}

Weather::~Weather()
{
    delete covered_objs;
}

//******************************************************************************
// WEATHER ACTIONS.
//******************************************************************************

std::vector <Action> * Weather::getActions()
{
    if(this -> steps > 0)
    {
        this -> steps--;
    }

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
