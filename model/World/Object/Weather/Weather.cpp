/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <sstream>

#include "Weather.h"

#include "../../../../common/BasicDefines.h"
#include "../../../../common/Math/Random.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Weather::Weather(WeatherType type, uint living_steps) :
    Object(WEATHER, false),
    subtype(type)
{
    this -> setShapeType(SHP_WEATHER);
    this -> setShapeSize(Random::double_range(SZ_WEATHER_DIAM_MIN, SZ_WEATHER_DIAM_MAX));
    this -> setDangerLevel(DNGR_WEATHER);
    this -> setWeight(WGHT_WEATHER);

    if(living_steps == 0)
    {
        this -> steps = Random::int_range(WEAT_STEPS_MIN, WEAT_STEPS_MAX);
    }
    else
    {
        this -> steps = living_steps;
    }
}

Weather::~Weather()
{
}

//******************************************************************************
// INHERETED THINGS.
//******************************************************************************

std::vector <Action> * Weather::getActions()
{
    if(this -> steps > 0)
    {
        this -> steps--;
    }

    this -> actions.clear();

    // TODO: Add actions for RAIN, CLOUDS, SNOW.

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
        for(iter = covered_objs.begin(); iter != covered_objs.end(); iter++)
        {
            act.addParticipant(*iter);
        }

        this -> actions.push_back(act);
    }

    return &(this -> actions);
}

void Weather::receiveMessage(Message message)
{
}

std::string Weather::getTypeName() const
{
    return "weather";
}
std::string Weather::printObjectInfo() const
{

}

//******************************************************************************
// HEALTH MANIPULATION.
//******************************************************************************

uint Weather::damage(uint delta)
{
    return 0;
}

uint Weather::heal(uint delta)
{
    return 0;
}

uint Weather::getHealthPoints() const
{
    return this -> steps;
}

uint Weather::getMaxHealthPoints() const
{
    return this -> steps;
}

//******************************************************************************
// WEATHER TYPE.
//******************************************************************************

WeatherType Weather::getSubtype() const
{
    return this -> subtype;
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

ObjectHeap * Weather::getCoveredObjects()
{
    return &(this -> covered_objs);
}

void Weather::setCoveredObjects(ObjectHeap heap)
{
    this -> covered_objs = heap;
}

uint Weather::getLivingSteps() const
{
    return this -> steps;
}
