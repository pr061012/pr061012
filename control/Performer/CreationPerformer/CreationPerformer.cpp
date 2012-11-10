/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "CreationPerformer.h"
#include "../../../model/BasicTypes.h"
#include "../../../model/BasicDefines.h"
#include "../../../model/World/ObjectFactory/ObjectFactory.h"

CreationPerformer::CreationPerformer(Indexator &indexator):
    indexator(indexator)
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

    if ((type != RESOURCE) || (type != CREATURE))
    {
        action.markAsFailed();
    }
    else
    {
        ObjectType obj_type = action.getParam<ObjectType>("obj_type");
        uint x = action.getParam<uint>("x");
        uint y = action.getParam<uint>("y");

        switch (obj_type)
        {
            case CREATURE:
                CreatureType creat_type = action.getParam<CreatureType>("creat_type");

                ParamArray param;
                param.addKey<CreatureType>("creat_type", creat_type);

                new_object = ObjectFactory.createObject(CREATURE, param);
                action.markAsSucceeded();
            break;

            case RESOURCE:
                ResourceType res_type = action.getParam<ResourceType>("res_type");
                uint res_amount = action.getParam<uint>("res_umount");

                ParamArray param;
                param.addKey<ResourceType>("res_type", res_type);
                param.addKey<uint>("res_amount", res_amount);

                new_object = ObjectFactory.createObject(CREATURE, param);
                action.markAsSucceeded();
            break;

            case TOOL:
                ToolType tool_type = action.getParam<ToolType>("tool_type");
                ResourceType mat_type = action.getParam<ResourceType>("mat_type");

                ParamArray param;
                param.addKey<ToolType>("tool_type", tool_type);
                param.addKey<ResourceType>("mat_type", mat_type);

                new_object = ObjectFactory.createObject(TOOL, param);
                action.markAsSucceeded();
            break;

            default:
                action.markAsFailed();
            break;
        }
    }
}
