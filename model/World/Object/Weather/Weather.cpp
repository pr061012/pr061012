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
    Object(WEATHER, false, true, true),
    subtype(type)
{
    // Initialising inhereted things.
    this -> makeFlying();
    this -> setShapeType(SHP_WEATHER);
    this -> setWeight(WGHT_WEATHER);

    // Setting danger level.
    switch (type)
    {
        case METEOR_SHOWER:
            this -> setDangerLevel(DNGR_WEATHER_METEOR_SHOWER);
            this -> setNormalSpeed(SPD_WEATHER_METEOR_SHOWER);
            this -> setShapeSize(Random::double_range(SZ_WEAT_METEOR_SHOWER_DIAM_MIN, SZ_WEAT_METEOR_SHOWER_DIAM_MAX));
        break;

        case HURRICANE:
            this -> setDangerLevel(DNGR_WEATHER_HURRICANE);
            this -> setNormalSpeed(SPD_WEATHER_HURRICANE);
            this -> setShapeSize(Random::double_range(SZ_WEAT_HURRICANE_DIAM_MIN, SZ_WEAT_HURRICANE_DIAM_MAX));
        break;

        case RAIN:
            this -> setDangerLevel(DNGR_WEATHER_RAIN);
            this -> setNormalSpeed(SPD_WEATHER_RAIN);
            this -> setShapeSize(Random::double_range(SZ_WEAT_RAIN_DIAM_MIN, SZ_WEAT_RAIN_DIAM_MAX));
        break;

        case CLOUDS:
            this -> setDangerLevel(DNGR_WEATHER_CLOUDS);
            this -> setNormalSpeed(SPD_WEATHER_CLOUDS);
            this -> setShapeSize(Random::double_range(SZ_WEAT_CLOUDS_DIAM_MIN, SZ_WEAT_CLOUDS_DIAM_MAX));
        break;
    }

    // Initialising living steps.
    if(living_steps == 0)
    {
        this -> steps = Random::int_range(WEAT_STEPS_MIN, WEAT_STEPS_MAX);
    }
    else
    {
        this -> steps = living_steps;
    }

    // Initialising direction angle.
    this -> direction_angle = Random::double_num(2 * M_PI);
    this -> roam_steps      = WEAT_ROAM_STEPS;

    // Initialising action steps.
    this -> action_steps    = WEAT_ACTION_STEPS;
}

Weather::~Weather()
{
}

//******************************************************************************
// INHERETED THINGS.
//******************************************************************************

std::vector<Action>* Weather::getActions()
{
    // Checking success of previous GO action.
    bool need_to_change_direction = false;
    for (uint i = 0; i < this -> actions.size(); i++)
    {
        Action act = this -> actions[i];
        if (act.getType() == GO && act.isFailed())
        {
            need_to_change_direction = true;
        }
    }
    this -> actions.clear();

    // Decreasing steps.
    if (this -> steps > 0)        this -> steps--;
    if (this -> roam_steps > 0)   this -> roam_steps--;
    if (this -> action_steps > 0) this -> action_steps--;

    // Changing direction (if needed).
    if (this -> roam_steps == 0 || need_to_change_direction)
    {
        this -> roam_steps = WEAT_ROAM_STEPS;
        this -> direction_angle = Random::double_num(2 * M_PI);
    }

    // Going in set direction.
    Action act(GO, this);
    act.addParam<double>("angle", this -> direction_angle);
    act.addParam<SpeedType>("speed", FAST_SPEED);
    this -> actions.push_back(act);

    // No need in new action generation
    // Note: HURRICANE is exception only for one reason, it moves all objects
    //       add should do it each step.
    if (this -> action_steps != 0 && this -> subtype != HURRICANE)
    {
        return &(this -> actions);
    }
    else
    {
        this -> action_steps = WEAT_ACTION_STEPS;
    }

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
            if (type == GRASS || type == TREE)
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

            act.addParticipant(*iter);
            act.addParam<double>("angle", v2.getAngle(v1) + 1.1 * M_PI / 2);
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
          insertSpaces("Type");
    switch (subtype)
    {
        case METEOR_SHOWER: ss << "meteor shower"; break;
        case RAIN:          ss << "rain";          break;
        case CLOUDS:        ss << "clouds";        break;
        case HURRICANE:     ss << "hurricane";     break;
    }
    ss << "\n";

    ss << insertSpaces("Direction angle") << direction_angle << std::endl <<
          insertSpaces("Roam steps")      << roam_steps << std::endl <<
          insertSpaces("Covered objects") << std::endl <<
                                             this -> covered_objs.printIDs() <<
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
