/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "../Object/Building/Building.h"
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
    Object * object;

    switch(type)
    {
        case BUILDING:
            object = createBuilding(params);
        break;

        case CREATURE:
        break;

        case RESOURCE:
        break;

        case TOOL:
        break;

        case WEATHER:
        break;
    }

    return object;
}

//******************************************************************************
// OBJECTS CREATION (INNER METHODS).
//******************************************************************************

Object * createBuilding(const ParamArray & params)
{
    unsigned int max_space = params.getValue("max_space");
    unsigned int max_health = params.getValue("max_health");

    Building * building = new Building(max_health, max_space);
}
