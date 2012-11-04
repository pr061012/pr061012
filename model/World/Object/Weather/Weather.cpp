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

    this -> actions.clear();

    if
    (
        this -> subtype == METEOR_SHOWER ||
        this -> subtype == STORM ||
        this -> subtype == HURRICANE ||
        this -> subtype == HAIL ||
        this -> subtype == EARTHQUAKE
    )
    {
        Action act(HARM_OBJS, this);

        // Add all objects to this action.
        ObjectHeap::const_iterator iter;
        for(iter = covered_objs -> begin(); iter != covered_objs -> end(); iter++)
        {
            act.addParticipant(*iter);
        }

        this -> actions.push_back(act);
    }

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
