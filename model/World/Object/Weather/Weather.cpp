/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <sstream>

#include "../../../../common/BasicDefines.h"
#include "../../../../common/Math/Random.h"
#include "../Resource/Resource.h"
#include "Weather.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Weather::Weather(WeatherType type, uint living_steps) :
    Object(WEATHER, false, false, true),
    subtype(type)
{
    this -> makeFlying();
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

std::vector<Action>* Weather::getActions()
{
    if(this -> steps > 0)
    {
        this -> steps--;
    }

    this -> actions.clear();

    // Meteor shower harms all objects.
    if (subtype == METEOR_SHOWER)
    {
        Action act(HARM_OBJS, this);

        ObjectHeap::const_iterator iter;
        for (iter = covered_objs.begin(); iter != covered_objs.end(); iter++)
        {
            act.addParticipant(*iter);
        }

        this -> actions.push_back(act);
    }
    // Rain heals food and bulding material.
    else if (subtype == RAIN)
    {
        ObjectHeap::const_iterator iter;
        for
        (
            iter = covered_objs.begin(RESOURCE);
            iter != covered_objs.end(RESOURCE);
            iter++
        )
        {
            Resource* res = dynamic_cast<Resource*>(*iter);
            ResourceType type = res -> getSubtype();
            if (type == RES_FOOD || type == RES_BUILDING_MAT)
            {
                Action act(REGENERATE_OBJ, this);
                act.addParticipant(res);
                act.addParam<uint>("object_index", 0);
                this -> actions.push_back(act);
            }
        }
    }
    // Hurricane moves all objects.
    else if (subtype == HURRICANE)
    {
        ObjectHeap::const_iterator iter;
        for (iter = covered_objs.begin(); iter != covered_objs.end(); iter++)
        {
            Action act(MOVE, this);

            Vector v1 = (*iter) -> getCoords();
            Vector v2 = this -> getCoords();

            act.addParam<double>("angle", v1.getAngle(v2));
            act.addParam<SpeedType>("speed", FAST_SPEED);

            this -> actions.push_back(act);
        }
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

std::string Weather::printObjectInfo(bool full) const
{
    std::stringstream ss;

    ss << Object::printObjectInfo(full) <<
          "Covered Object" << std::endl << this -> covered_objs.printIDs() <<
                              std::endl;

    return ss.str();
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
