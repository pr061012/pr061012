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

ObjectFactory::ObjectFactory()
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
    unsigned int max_space = params.getValue("max_space");
    unsigned int max_health = params.getValue("max_health");

    return new Building(max_health, max_space);
}

Object * ObjectFactory::createCreature(const ParamArray & params)
{
    CreatureType type = static_cast<CreatureType>(params.getValue("creat_type"));

    Object * obj = NULL;

    // TODO: How to pass DecisionMaker?
    switch(type)
    {
        case HUMANOID:
            //obj = new Humanoid(NULL);
        break;

        case NON_HUMANOID:
            //obj = new NonHumanoid(NULL);
        break;
    }

    return obj;
}

Object * ObjectFactory::createResource(const ParamArray & params)
{
    ResourceType type = static_cast<ResourceType>(params.getValue("res_type"));
    int amount = params.getValue("res_amount");

    return new Resource(type, amount);
}

Object * ObjectFactory::createTool(const ParamArray & params)
{
    ToolType type = static_cast<ToolType>(params.getValue("tool_type"));
    ResourceType mat_type = static_cast<ResourceType>(params.getValue("mat_type"));

    return new Tool(type, mat_type);
}

Object * ObjectFactory::createWeather(const ParamArray & params)
{
    WeatherType type = static_cast<WeatherType>(params.getValue("weat_type"));

    return new Weather(type);
}
