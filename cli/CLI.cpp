/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "CLI.h"

#include <sstream>

//******************************************************************************
// CONSTRUCTOR.
//******************************************************************************

CLI::CLI(World* world, Controller* control) :
    world(world),
    control(control)
{
}

//******************************************************************************
// RUNNING COMMANDS.
//******************************************************************************

std::string CLI::runCommand(std::string command)
{
    // Creating string stream.
    std::stringstream ss(command);

    // Reading command.
    std::string cmd;
    ss >> cmd;

    // Running processors.
    if (cmd == "init")
    {
        return this -> init(ss, false);
    }

    if (cmd == "random-init")
    {
        return this -> init(ss, true);
    }

    if (cmd == "create")
    {
        return this -> create(ss);
    }

    if (cmd == "list")
    {
        return this -> list(ss);
    }

    if (cmd == "info")
    {
        return this -> info(ss);
    }

    if (cmd == "change")
    {
        return this -> change(ss);
    }

    if (cmd == "step")
    {
        return this -> step(ss);
    }

    if (cmd == "trace-step")
    {
        return this -> traceStep(ss);
    }

    return "Unknown command `" + cmd + "`.\n";
}

//******************************************************************************
// COMMAND'S PROCESSORS.
//******************************************************************************

std::string CLI::init(std::stringstream &ss, bool random)
{
    // FIXME: Interpreting only one size.
    int size = -1;
    ss >> size;

    if (ss.fail())
    {
        return std::string("Error: Integer argument expected.\n") +
               std::string("Syntax: init <size>\n");
    }

    if (size <= 0)
    {
        return "Error: Size must be greater than 0.\n";
    }

    this -> world -> reset(size, random);
    return "Successfully created world.\n";
}

std::string CLI::create(std::stringstream& ss)
{
    // Reading type.
    ObjectType obj_type;
    std::string type;
    ss >> type;
    if (ss.fail())
    {
        return std::string("Error: ObjectType argument expected.\n") +
               std::string("Syntax: create <x> <y> <type> [additional args]\n");
    }

    // Reading additional args depending on ObjectType.
    ParamArray pa;
    if (type == "CREATURE")
    {
        obj_type = CREATURE;

        std::string creat_type;
        ss >> creat_type;
        if (ss.fail())
        {
            return std::string("Error: CreatureType argument expected.\n") +
                   std::string("Syntax: create <x> <y> <CreatureType>\n");
        }

        if (creat_type == "HUMANOID")
        {
            pa.addKey<CreatureType>("creat_type", HUMANOID);
        }
        else if (creat_type == "NON_HUMANOID")
        {
            pa.addKey<CreatureType>("creat_type", NON_HUMANOID);
        }
        else
        {
            return std::string("Error: Unknown CreatureType.\n");
        }
    }
    else if (type == "BUILDING")
    {
        obj_type = BUILDING;

        uint max_health, max_space;

        ss >> max_health;
        if (ss.fail())
        {
            return std::string("Error: max_health expected.\n") +
                   std::string("Syntax: create <x> <y> BUILDING <max_health> <max_space>\n");
        }

        ss >> max_space;
        if (ss.fail())
        {
            return std::string("Error: max_space expected.\n") +
                   std::string("Syntax: create <x> <y> BUILDING <max_health> <max_space>\n");
        }

        pa.addKey<uint>("max_health", max_health);
        pa.addKey<uint>("max_space", max_space);
    }
    else if (type == "RESOURCE")
    {
        obj_type = RESOURCE;

        std::string res_type;
        ss >> res_type;
        if (ss.fail())
        {
            return std::string("Error: ResourceType expected.\n") +
                   std::string("Syntax: create <x> <y> RESOURCE <res_type> <res_amount>");
        }

        if (ss == "RES_FOOD")
        {
            pa.addKey<ResourceType>("res_type", RES_FOOD);
        }
        else if (ss == "RES_BUILDING_MAT")
        {
            pa.addKey<ResourceType>("res_type", RES_BUILDING_MAT);
        }
        else
        {
            return std::string("Error: unknown ResourceType.\n");
        }

        uint res_amount;
        ss >> res_amount;
        if (ss.fail())
        {
            return std::string("Error: res_amount expected.\n") +
                   std::string("Syntax: create <x> <y> RESOURCE <res_type> <res_amount>");
        }

        pa.addKey<uint>("res_amount", res_amount);
    }
    else if (type == "WEATHER")
    {
        obj_type = WEATHER;

        // FIXME: Ignoring weather type.
        uint weat_steps;
        ss >> weat_steps;
        if (ss.fail())
        {
            return std::string("Error: weat_steps expected.\n") +
                   std::string("Syntax: create <x> <y> WEATHER <weat_steps>");
        }

        pa.addKey<uint>("weat_steps", weat_steps);
    }
    else
    {
        return std::string("Error: unknown ObjectType.\n");
    }

    // Creating object.
    ObjectFactory* obj_factory = this -> world -> getObjectFactory();
    Object* obj = obj_factory -> createObject(obj_type, pa);
    this -> world -> addObject(true, obj);
}

std::string CLI::list(std::stringstream& ss)
{
    std::string output;

    // Listing visible objects.
    ObjectHeap* objs = this -> world -> getVisibleObjects();
    ObjectHeap::const_iterator iter;
    for (iter = objs -> begin(); iter != objs -> end(); iter++)
    {
        Object* obj = *iter;
        output += std::to_string(obj -> getObjectID()) + "\t|";
        output += std::to_string(obj -> getType()) + "\t|\n";
    }

    return output;
    // TODO: Listing hidden objects.
    //ObjectHeap* hidden_objs = this -> world -> getHiddenObjects();
}

std::string CLI::info(std::stringstream& ss)
{
}

std::string CLI::step(std::stringstream& ss)
{
    this -> control -> step();
    return "Successfully updated world.\n";
}

std::string CLI::traceStep(std::stringstream& ss)
{
}

std::string CLI::change(std::stringstream& ss)
{
}
