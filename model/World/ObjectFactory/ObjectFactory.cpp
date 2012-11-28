/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>

#include "../Object/Building/Building.h"
#include "../Object/Creatures/Creature.h"
#include "../Object/Resource/Resource.h"
#include "../Object/Tool/Tool.h"
#include "../Object/Weather/Weather.h"
#include "../Object/Creatures/Humanoid/Humanoid.h"
#include "../Object/Creatures/NonHumanoid/NonHumanoid.h"

#include "ObjectFactory.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

ObjectFactory::ObjectFactory(const DecisionMaker& hum_dmaker,
                             const DecisionMaker& nhum_dmaker) :
    hum_dmaker(hum_dmaker),
    nhum_dmaker(nhum_dmaker)
{
}

ObjectFactory::~ObjectFactory()
{
}

//******************************************************************************
// OBJECT'S CREATION.
//******************************************************************************

Object * ObjectFactory::createObject(ObjectType type, const ParamArray & params)
{
    Object * object = NULL;

    switch(type)
    {
        case BUILDING:
            object = createBuilding(params);
        break;

        case CREATURE:
            object = createCreature(params);
        break;

        case RESOURCE:
            object = createResource(params);
        break;

        case TOOL:
            object = createTool(params);
        break;

        case WEATHER:
            object = createWeather(params);
        break;
    }

    return object;
}

//******************************************************************************
// OBJECTS CREATION (INNER METHODS).
//******************************************************************************

Object * ObjectFactory::createBuilding(const ParamArray & params)
{
    uint max_space = params.getValue<uint>("max_space");
    uint max_health = params.getValue<uint>("max_health");

    return new Building(max_health, max_space);
}

Object * ObjectFactory::createCreature(const ParamArray & params)
{
    CreatureType type = params.getValue<CreatureType>("creat_type");

    Object * obj = NULL;

    switch(type)
    {
        case HUMANOID:
            obj = new Humanoid(this -> hum_dmaker);
        break;

        case NON_HUMANOID:
            obj = new NonHumanoid(this -> nhum_dmaker);
        break;
    }

    return obj;
}

Object * ObjectFactory::createResource(const ParamArray & params)
{
    ResourceType type = params.getValue<ResourceType>("res_type");
    uint amount;

    try
    {
        amount = params.getValue<uint>("res_amount");
    }
    catch (EParamArrayInvalidKey& exc)
    {
        amount = 0;
    }

    return new Resource(type, amount);
}

Object * ObjectFactory::createTool(const ParamArray & params)
{
    ToolType type = params.getValue<ToolType>("tool_type");
    ResourceType mat_type = params.getValue<ResourceType>("mat_type");
    uint max_strength;

    try
    {
        max_strength = params.getValue<uint>("tool_str");
    }
    catch (EParamArrayInvalidKey& exc)
    {
        max_strength = 0;
    }

    return new Tool(type, mat_type, max_strength);
}

Object * ObjectFactory::createWeather(const ParamArray & params)
{
    WeatherType type = params.getValue<WeatherType>("weat_type");
    uint steps;

    try
    {
        steps = params.getValue<uint>("weat_steps");
    }
    catch (EParamArrayInvalidKey& exc)
    {
        steps = 0;
    }

    return new Weather(type, steps);
}
