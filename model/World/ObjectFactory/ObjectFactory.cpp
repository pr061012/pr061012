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

Object * ObjectFactory::createObject(ObjectType type, const std::map <std::string, int> & params)
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

Object * createBuilding(const std::map <std::string, int> & params)
{
    Building * building = new Building;
}
