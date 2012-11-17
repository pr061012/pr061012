/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "CreationPerformer.h"
#include "../../../common/BasicTypes.h"
#include "../../../common/BasicDefines.h"
#include "../../../model/World/ObjectFactory/ObjectFactory.h"
#include "../../../model/World/Object/Creatures/Creature.h"
#include "../../../model/World/Object/Resource/Resource.h"

CreationPerformer::CreationPerformer(World* world):
    indexator(world -> getIndexator()),
    world(world),
    factory(world -> getObjectFactory())
{

}

CreationPerformer::~CreationPerformer()
{

}

void CreationPerformer::perform(Action& action)
{
    Object* actor = action.getActor();
    Object* new_object;
    ObjectType type = actor -> getType();

    ObjectType obj_type = action.getParam<ObjectType>("obj_type");

    uint x = action.getParam<double>("x");
    uint y = action.getParam<double>("y");

    ParamArray param;
    param.addKey<double>("x", x);
    param.addKey<double>("y", y);

    if (( type == RESOURCE || type == CREATURE ) && checkCoord(x, y))
    {
        switch (obj_type)
        {
            case CREATURE:
            {
                new_object = createCreature(action, param);
                world -> addObject(true, new_object);

                action.markAsSucceeded();
            }
            break;

            case RESOURCE:
            {
                new_object = createResource(action, param);
                world -> addObject(false, new_object);
                if (type == RESOURCE)
                {
                    static_cast<Resource*>(actor) -> increaseAmount(1);
                }

                action.markAsSucceeded();
            }
            break;

            case TOOL:
            {
                new_object = createTool(action, param);
                world -> addObject(false, new_object);

                action.markAsSucceeded();
            }
            break;

            case BUILDING:
            {
                new_object = createBuilding(action, param);
                world -> addObject(true, new_object);

                action.markAsSucceeded();
            }
            break;

            default:
                action.markAsFailed();
            break;
        }
    }
    else
    {
        action.markAsFailed();
    }
}

bool CreationPerformer::checkCoord(double x, double y)
{
    bool ret = false;
    Shape ghost;
    Point coord = Point(x, y);

    ghost.setCenter(coord);

    ObjectHeap obstacles = indexator -> getAreaContents(ghost);
    if (!obstacles.getTypeAmount(CREATURE) &&
        !obstacles.getTypeAmount(BUILDING))
    {
        ret = true;
    }

    return ret;
}

Object* CreationPerformer::createBuilding(Action& action, ParamArray& param)
{
    uint max_health = action.getParam<uint>("max_health");
    uint max_space = action.getParam<uint>("max_space");

    param.addKey<uint>("max_health",max_health);
    param.addKey<uint>("max_space",max_space);

    return factory -> createObject(BUILDING, param);
}

Object* CreationPerformer::createCreature(Action& action, ParamArray& param)
{
    CreatureType creat_type = action.getParam<CreatureType>("creat_type");

    param.addKey<CreatureType>("creat_type", creat_type);

    return factory -> createObject(CREATURE, param);
}

Object* CreationPerformer::createResource(Action& action, ParamArray& param)
{
    ResourceType res_type = action.getParam<ResourceType>("res_type");
    uint res_amount = action.getParam<uint>("res_amount");

    param.addKey<ResourceType>("res_type", res_type);
    param.addKey<uint>("res_amount", res_amount);

    return factory -> createObject(RESOURCE, param);
}

Object* CreationPerformer::createTool(Action& action, ParamArray& param)
{
    ToolType tool_type = action.getParam<ToolType>("tool_type");
    ResourceType mat_type = action.getParam<ResourceType>("mat_type");
    uint tool_str = action.getParam<uint>("tool_str");

    param.addKey<ToolType>("tool_type", tool_type);
    param.addKey<ResourceType>("mat_type", mat_type);
    param.addKey<uint>("tool_str",tool_str);

    return factory -> createObject(TOOL, param);
}
