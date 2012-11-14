/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

// TODO: Resource can create any objects (change)
//      Add created object in inventory
// Add comment

#include "CreationPerformer.h"
#include "../../../model/BasicTypes.h"
#include "../../../model/BasicDefines.h"
#include "../../../model/World/ObjectFactory/ObjectFactory.h"
#include "../../../model/World/Object/Creatures/Creature.h"

CreationPerformer::CreationPerformer(Indexator &indexator, World* world):
    indexator(indexator),
    world(world)
{
    factory = world->getObjectFactory();
}

CreationPerformer::~CreationPerformer()
{

}

void CreationPerformer::perform(Action& action)
{
    Object* actor = action.getActor();
    Object* new_object;
    ObjectType type = actor -> getType();

    if ((type != RESOURCE) || (type != CREATURE))
    {
        action.markAsFailed();
    }
    else
    {
        ObjectType obj_type = action.getParam<ObjectType>("obj_type");

        uint x = action.getParam<uint>("x");
        uint y = action.getParam<uint>("y");

        ParamArray param;
        param.addKey<uint>("x", x);
        param.addKey<uint>("y", y);

        if (checkCoord(x, y))
        {
            switch (obj_type)
            {
                case CREATURE:
                {
                    CreatureType creat_type = action.getParam<CreatureType>("creat_type");

                    param.addKey<CreatureType>("creat_type", creat_type);

                    new_object = factory->createObject(CREATURE, param);
                    world->addObject(true, new_object);

                    action.markAsSucceeded();
                }
                break;

                case RESOURCE:
                {
                    ResourceType res_type = action.getParam<ResourceType>("res_type");
                    uint res_amount = action.getParam<uint>("res_amount");

                    param.addKey<ResourceType>("res_type", res_type);
                    param.addKey<uint>("res_amount", res_amount);

                    new_object = factory->createObject(CREATURE, param);
                    world->addObject(false, new_object);

                    action.markAsSucceeded();
                }
                break;

                case TOOL:
                {
                    ToolType tool_type = action.getParam<ToolType>("tool_type");
                    ResourceType mat_type = action.getParam<ResourceType>("mat_type");
                    uint tool_str = action.getParam<uint>("tool_str");

                    param.addKey<ToolType>("tool_type", tool_type);
                    param.addKey<ResourceType>("mat_type", mat_type);
                    param.addKey<uint>("tool_str",tool_str);

                    new_object = factory->createObject(TOOL, param);
                    world->addObject(false, new_object);

                    action.markAsSucceeded();
                }
                break;

                case BUILDING:
                {
                    uint max_health = action.getParam<uint>("max_health");
                    uint max_space = action.getParam<uint>("max_space");

                    param.addKey<uint>("max_health",max_health);
                    param.addKey<uint>("max_space",max_space);

                    new_object = factory->createObject(BUILDING, param);
                    world->addObject(true, new_object);

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
}

bool CreationPerformer::checkCoord(uint x, uint y)
{
    bool ret = false;
    Shape ghost;
    Point coord = Point(x, y);

    ghost.setCenter(coord);

    ObjectHeap obstacles = indexator.getAreaContents(ghost);
    if (!obstacles.getTypeAmount(CREATURE) &&
        !obstacles.getTypeAmount(BUILDING))
    {
        ret = true;
    }

    return ret;
}
