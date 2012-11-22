/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "CLI.h"

#include <sstream>

#include "../model/Utilities/Vector/Vector.h"
#include "../model/World/Object/Creatures/Creature.h"
#include "../model/World/Object/Creatures/Humanoid/Humanoid.h"
#include "../model/World/Object/Creatures/NonHumanoid/NonHumanoid.h"

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
    // Reading coordinates.
    double x;
    ss >> x;
    if (ss.fail())
    {
        return std::string("Error: x coordinate expected.\n") +
               std::string("Syntax: create <x> <y> <type> [additional args]\n");
    }

    double y;
    ss >> y;
    if (ss.fail())
    {
        return std::string("Error: y coordinate expected.\n") +
               std::string("Syntax: create <x> <y> <type> [additional args]\n");
    }

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
    obj -> setCoords(Vector(x, y));
    this -> world -> addObject(true, obj);

    return std::string("Succesfully created object (id is ") +
           std::to_string(obj -> getObjectID()) +
           std::string(").\n");
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
    std::string output;

    // Reading id.
    uint id;
    ss >> id;
    if (ss.fail())
    {
        return std::string("Error: object id expected.\n") +
               std::string("Syntax: info <id>\n");
    }

    // Looking for object.
    ObjectHeap* objs = this -> world -> getVisibleObjects();
    ObjectHeap::const_iterator iter;
    Object* obj;
    for (iter = objs -> begin(); iter != objs -> end(); iter++)
    {
        obj = *iter;

        if (obj -> getObjectID() == id)
        {
            break;
        }
    }

    if (iter == objs -> end())
    {
        return std::string("Error: object with id ") +
               std::to_string(id) +
               std::string(" doesn't exist.\n");
    }

    // Getting object information.
    ObjectType type = obj -> getType();

    // Coordinates and angle.
    Vector v = obj -> getCoords();
    output += std::string("X:\t\t\t") + std::to_string(v.getX()) + "\n";
    output += std::string("Y:\t\t\t") + std::to_string(v.getY()) + "\n";
    output += std::string("Angle:\t\t\t") + std::to_string(obj -> getAngle()) + "\n";

    // Shape type.
    ShapeType shape = obj -> getShape().getType();
    output += std::string("Shape:\t\t\t");
    if (shape == CIRCLE)
    {
        output += "CIRCLE\n";
    }
    else if (shape == SQUARE)
    {
        output += "SQUARE\n";
    }

    // Danger level.
    output += std::string("Danger level:\t\t") + std::to_string(obj -> getDangerLevel()) + "\n";

    // HP.
    output += std::string("HP:\t\t\t") + std::to_string(obj -> getHealthPoints()) + "\n";
    output += std::string("Max HP:\t\t\t") + std::to_string(obj -> getMaxHealthPoints()) + "\n";

    if (type == CREATURE)
    {
        output += "Type:\t\t\tCREATURE\n";

        Creature* creat = dynamic_cast<Creature*>(obj);
        CreatureType subtype = creat -> getSubtype();

        // Printing age.
        output += std::string("Age:\t\t\t") + std::to_string(creat -> getAge()) +
                  std::string("/") + std::to_string(creat -> getMaxAge()) +
                  std::string("\n");

        // Printing decision.
        output += std::string("Current decision:\t") +
                  std::to_string(creat -> getCurrentDecision()) + "\n";

        // Printing view area.
        Shape view_area = creat -> getViewArea();
        output += std::string("View area size:\t\t") + std::to_string(view_area.getSize()) + "\n";
        output += std::string("View area shape:\t");
        if (view_area.getType() == CIRCLE)
        {
            output += "CIRCLE\n";
        }
        else if (view_area.getType() == SQUARE)
        {
            output += "SQUARE\n";
        }

        // TODO: Print inventory, objects around.

        if (subtype == HUMANOID)
        {
            output += "Subtype:\t\tHUMANOID\n";

            Humanoid* hum = dynamic_cast<Humanoid*>(creat);

            // TODO: Print visual memory, humanoid id.
        }
        else if (subtype == NON_HUMANOID)
        {
            output += "Subtype:\t\tNON_HUMANOID\n";

            NonHumanoid* nhum = dynamic_cast<NonHumanoid*>(creat);
        }
    }

    return output;
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
