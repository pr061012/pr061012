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
    Object * actor = action.getActor();
    ObjectType type = actor -> getType();

    if ((type != RESOURCE) || (type != CREATURE))
    {
        action.markAsFailed();
    }
    else
    {
        ObjectType obj_type = action.getParam<ObjectType>("obj_type");
        int x = action.getParam<int>("x");
        int y = action.getParam<int>("y");

        switch (obj_type)
        {
            case CREATURE:
                CreatureType creat_type = action.getParam<CreatureType>("creat_type");

            break;

            case RESOURCE:

            break;

            case TOOL:
                ToolType tool_type = action.getParam<ToolType>("tool_type");
                ResourceType mat_type = action.getParam<ResourceType>("mat_type");

            break;

            default:
                action.markAsFailed();
            break;
        }
    }
}
