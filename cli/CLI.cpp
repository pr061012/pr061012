/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "CLI.h"

#include <cstdarg>
#include <sstream>

#include "../model/Utilities/Vector/Vector.h"
#include "../model/World/Object/Resource/Resource.h"
#include "../model/World/Object/Creatures/Creature.h"
#include "../model/World/Object/Creatures/Humanoid/Humanoid.h"
#include "../model/World/Object/Creatures/NonHumanoid/NonHumanoid.h"

//******************************************************************************
// TRUNCATED NAMES.
// Prefix: TN.
//******************************************************************************

#define TN_CREATURE                 "c"
#define TN_HUMANOID                 "h"
#define TN_NON_HUMANOID             "nh"
#define TN_BUILDING                 "b"
#define TN_RESOURCE                 "r"
#define TN_RESOURCE_FOOD            "f"
#define TN_RESOURCE_BUILDING_MAT    "bm"
#define TN_WEATHER                  "w"

//******************************************************************************
// STATIC FUNCTIONS.
//******************************************************************************

// Insolent copypaste:
// http://stackoverflow.com/a/8098080
std::string sformat(const std::string& format, ...)
{
    int size = 100;
    std::string result;
    va_list ap;

    while (true)
    {
        result.resize(size);

        va_start(ap, format);
        int n = vsnprintf((char *) result.c_str(), size, format.c_str(), ap);
        va_end(ap);

        if (n > -1 && n < size)
        {
            result.resize(n);
            break;
        }

        if (n > -1)
        {
            size = n + 1;
        }
        else
        {
            size *= 2;
        }
    }

    return result;
}

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

    return sformat("Unknown command `%s`.\n", cmd.c_str());
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
        return sformat("Error: integer argument expected.\n") +
               sformat("Syntax: init <size>\n");
    }

    if (size < 50)
    {
        return sformat("Error: size must be greater than 50 (%d is given).\n",
                       size);
    }

    this -> world -> reset(size, random);
    return sformat("Successfully created world %dx%d.\n", size, size);
}

std::string CLI::create(std::stringstream& ss)
{
    // Reading coordinates.
    double x;
    ss >> x;
    if (ss.fail())
    {
        return sformat("Error: x coordinate expected.\n") +
               sformat("Syntax: create <x> <y> <type> [additional args]\n");
    }

    double y;
    ss >> y;
    if (ss.fail())
    {
        return sformat("Error: y coordinate expected.\n") +
               sformat("Syntax: create <x> <y> <type> [additional args]\n");
    }

    // Reading type.
    ObjectType obj_type;
    std::string type;
    ss >> type;
    if (ss.fail())
    {
        return sformat("Error: ObjectType expected.\n") +
               sformat("Syntax: create <x> <y> <type> [additional args]\n");
    }

    // Reading additional args depending on ObjectType.
    ParamArray pa;
    if (type == TN_CREATURE)
    {
        obj_type = CREATURE;

        std::string creat_type;
        ss >> creat_type;
        if (ss.fail())
        {
            return sformat("Error: CreatureType expected.\n") +
                   sformat("Syntax: create <x> <y> %s <CreatureType>\n",
                           TN_CREATURE);
        }

        if (creat_type == TN_HUMANOID)
        {
            pa.addKey<CreatureType>("creat_type", HUMANOID);
        }
        else if (creat_type == TN_NON_HUMANOID)
        {
            pa.addKey<CreatureType>("creat_type", NON_HUMANOID);
        }
        else
        {
            return sformat("Error: Unknown CreatureType (%s), possible values: %s, %s.\n",
                           creat_type.c_str(), TN_HUMANOID, TN_NON_HUMANOID);
        }
    }
    else if (type == TN_BUILDING)
    {
        obj_type = BUILDING;

        uint max_health, max_space;

        ss >> max_health;
        if (ss.fail())
        {
            return sformat("Error: max_health expected.\n") +
                   sformat("Syntax: create <x> <y> %s <max_health> <max_space>\n",
                           TN_BUILDING);
        }

        ss >> max_space;
        if (ss.fail())
        {
            return sformat("Error: max_space expected.\n") +
                   sformat("Syntax: create <x> <y> %s <max_health> <max_space>\n",
                           TN_BUILDING);
        }

        pa.addKey<uint>("max_health", max_health);
        pa.addKey<uint>("max_space", max_space);
    }
    else if (type == TN_RESOURCE)
    {
        obj_type = RESOURCE;

        std::string res_type;
        ss >> res_type;
        if (ss.fail())
        {
            return sformat("Error: ResourceType expected.\n") +
                   sformat("Syntax: create <x> <y> %s <res_type> <res_amount>\n",
                           TN_RESOURCE);
        }

        if (ss == TN_RESOURCE_FOOD)
        {
            pa.addKey<ResourceType>("res_type", RES_FOOD);
        }
        else if (ss == TN_RESOURCE_BUILDING_MAT)
        {
            pa.addKey<ResourceType>("res_type", RES_BUILDING_MAT);
        }
        else
        {
            return sformat("Error: unknown ResourceType (%s), possible values: %s, %s.\n",
                           res_type.c_str(), TN_RESOURCE_FOOD, TN_RESOURCE_BUILDING_MAT);
        }

        uint res_amount;
        ss >> res_amount;
        if (ss.fail())
        {
            return sformat("Error: res_amount expected.\n") +
                   sformat("Syntax: create <x> <y> %s <res_type> <res_amount>\n",
                           TN_RESOURCE);
        }

        pa.addKey<uint>("res_amount", res_amount);
    }
    else if (type == TN_WEATHER)
    {
        obj_type = WEATHER;

        // FIXME: Ignoring weather type.
        pa.addKey<WeatherType>("weat_type", METEOR_SHOWER);

        uint weat_steps;
        ss >> weat_steps;
        if (ss.fail())
        {
            return sformat("Error: weat_steps expected.\n") +
                   sformat("Syntax: create <x> <y> %s <weat_steps>\n",
                           TN_WEATHER);
        }

        pa.addKey<uint>("weat_steps", weat_steps);
    }
    else
    {
        return sformat("Error: unknown ObjectType (%s), possible values: %s, %s, %s, %s\n",
                       type.c_str(), TN_BUILDING, TN_CREATURE, TN_RESOURCE, TN_WEATHER);
    }

    // Creating object.
    ObjectFactory* obj_factory = this -> world -> getObjectFactory();
    Object* obj = obj_factory -> createObject(obj_type, pa);
    obj -> setCoords(Vector(x, y));
    this -> world -> addObject(true, obj);

    return sformat("Succesfully created object (id is %d).\n",
                   obj -> getObjectID());
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
        output += sformat("|%d\t|%d\t|", obj -> getObjectID(),
                          obj -> getType());
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
        return sformat("Error: object id expected.\n") +
               sformat("Syntax: info <id>\n");
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
        return sformat("Error: object with id %d doesn't exist.\n", id);
    }

    output += "\n========= COMMON INFORMATION =========\n";
    output += sformat("ID\t\t\t%d\n", obj -> getObjectID());

    // Getting object information.
    ObjectType type = obj -> getType();

    // Coordinates and angle.
    Vector v = obj -> getCoords();
    output += sformat("X\t\t\t%f\n", v.getX());
    output += sformat("Y\t\t\t%f\n", v.getY());
    output += sformat("Angle\t\t\t%f\n", obj -> getAngle());

    // Shape type.
    Shape shape = obj -> getShape();
    output += sformat("Shape\t\t\t%s (%f)\n",
                      shape.getType() == CIRCLE ? "CIRCLE" : "SQUARE",
                      shape.getSize());

    // Is destroyed, solid or immort.
    output += sformat("Is destroyed\t\t%s\n",
                      obj -> isDestroyed() ? "yes" : "no");
    output += sformat("Is solid\t\t%s\n",
                      obj -> isSolid() ? "yes" : "no");
    output += sformat("Is immortal\t\t%s\n",
                      obj -> isImmortal() ? "yes" : "no");

    // Danger level.
    output += sformat("Danger level\t\t%u\n", obj -> getDangerLevel());

    // HP.
    output += sformat("HP\t\t\t%d/%d\n", obj -> getHealthPoints(),
                      obj -> getMaxHealthPoints());

    if (type == BUILDING)
    {
        output += "Type:\t\t\tBUILDING\n";
        output += "======== BUILDING INFORMATION ========\n";

        Building* building = dynamic_cast<Building*>(obj);

        // Completness.
        output += sformat("Is complete\t\t%s\n",
                          building -> getCompleteness() ? "yes" : "no");
    }
    else if (type == RESOURCE)
    {
        output += "Type:\t\t\tRESOURCE\n";
        output += "======== RESOURCE INFORMATION ========\n";

        Resource* res = dynamic_cast<Resource*>(obj);

        // Mineability and restorability.
        output += sformat("Is mineable\t\t%s\n",
                          res -> isMineable() ? "yes" : "no");
        output += sformat("Is restorable\t%s\n",
                          res -> isRestorable() ? "yes" : "no");

        // Difficulty and progress.
        output += sformat("Difficulty\t\t%u\n", res -> getDifficulty());
        output += sformat("Progress\t\t%u\n", res -> getProgress());
    }
    else if (type == CREATURE)
    {
        output += "Type:\t\t\tCREATURE\n";
        output += "======== CREATURE INFORMATION ========\n";

        Creature* creat = dynamic_cast<Creature*>(obj);
        CreatureType subtype = creat -> getSubtype();

        // Printing age.
        output += sformat("Age\t\t\t%d/%d\n", creat -> getAge(),
                          creat -> getMaxAge());

        // Printing decision.
        output += sformat("Current decision\t%d\n",
                          creat -> getCurrentDecision());

        // Printing view area.
        Shape view_area = creat -> getViewArea();
        output += sformat("View area\t\t%s (%f)\n",
                          view_area.getType() == CIRCLE ? "CIRCLE" : "SQUARE",
                          view_area.getSize());

        // Printing inventory.
        output += "Inventory\t\t";
        ObjectHeap* inv = creat -> getInventory();
        ObjectHeap::const_iterator iter;
        for (iter = inv -> begin(); iter != inv -> end(); iter++)
        {
            output += sformat("%d\t", (*iter) -> getObjectID());
        }
        output += "\n";

        // Printing objects around.
        output += "Objects around\t";
        ObjectHeap* objs_around = creat -> getObjectsAround();
        for (iter = objs_around -> begin(); iter != objs_around -> end(); iter++)
        {
            output += sformat("%d\t", (*iter) -> getObjectID());
        }
        output += "\n";

        if (subtype == HUMANOID)
        {
            output += "Subtype\t\t\tHUMANOID\n";
            output += "======== HUMANOID INFORMATION ========\n";

            Humanoid* hum = dynamic_cast<Humanoid*>(creat);

            output += sformat("Humanoid ID\t\t%d\n", hum -> getHumanoidID());
        }
        else if (subtype == NON_HUMANOID)
        {
            output += "Subtype\t\t\tNON_HUMANOID\n";
            output += "====== NON-HUMANOID INFORMATION ======\n";

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
