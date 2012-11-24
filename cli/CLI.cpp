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
    // Initialising array with object types names.
    this -> obj_types.resize(AMNT_OBJECT_TYPES);
    this -> obj_types[RESOURCE] = "RESOURCE";
    this -> obj_types[BUILDING] = "BUILDING";
    this -> obj_types[TOOL]     = "TOOL    ";
    this -> obj_types[WEATHER]  = "WEATHER ";
    this -> obj_types[CREATURE] = "CREATURE";

    // Initialising array with creature types names.
    this -> creat_types.resize(AMNT_CREATURE_TYPES);
    this -> creat_types[HUMANOID]     = "HUMANOID    ";
    this -> creat_types[NON_HUMANOID] = "NON_HUMANOID";

    // Initialising array with shape types names.
    this -> shape_types.resize(AMNT_SHAPE_TYPES);
    this -> shape_types[CIRCLE] = "CIRCLE";
    this -> shape_types[SQUARE] = "SQUARE";

    // Initialising array with creature actions names.
    this -> creat_acts.resize(AMNT_CREATURE_ACTS);
    this -> creat_acts[NONE]          = "NONE";
    this -> creat_acts[SLEEP]         = "SLEEP";
    this -> creat_acts[EAT]           = "EAT";
    this -> creat_acts[BUILD]         = "BUILD";
    this -> creat_acts[GATHER]        = "GATHER";
    this -> creat_acts[RELAX]         = "RELAX";
    this -> creat_acts[EXPLORE]       = "EXPLORE";
    this -> creat_acts[COMMUNICATE]   = "COMMUNICATE";
    this -> creat_acts[WORK]          = "WORK";
    this -> creat_acts[REALIZE_DREAM] = "REALIZE_DREAM";
    this -> creat_acts[ESCAPE]        = "ESCAPE";
    this -> creat_acts[REPRODUCE]     = "REPRODUCE";
    this -> creat_acts[DO_NOTHING]    = "DO_NOTHING";

    // Initialising array with detailed humanoid action types.
    this -> hum_acts.resize(AMNT_DET_HUM_ACTS);
    this -> hum_acts[HUNT]                     = "HUNT";
    this -> hum_acts[TAKE_FOOD_FROM_INVENTORY] = "TAKE_FOOD_FROM_INVENTORY";
    this -> hum_acts[FIND_FOOD]                = "FIND_FOOD";
    this -> hum_acts[RELAX_AT_HOME]            = "RELAX_AT_HOME";
    this -> hum_acts[SLEEP_AT_HOME]            = "SLEEP_AT_HOME";
    this -> hum_acts[SLEEP_ON_THE_GROUND]      = "SLEEP_ON_THE_GROUND";
    this -> hum_acts[BUILD_HOUSE]              = "BUILD_HOUSE";
    this -> hum_acts[CHOOSE_PLACE_FOR_HOME]    = "CHOOSE_PLACE_FOR_HOME";
    this -> hum_acts[FIGHT]                    = "FIGHT";
    this -> hum_acts[RUN_FROM_DANGER]          = "RUN_FROM_DANGER";
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
// `INIT` PROCESSOR.
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

//******************************************************************************
// `CREATE` PROCESSOR.
//******************************************************************************

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

        if (res_type == TN_RESOURCE_FOOD)
        {
            pa.addKey<ResourceType>("res_type", RES_FOOD);
        }
        else if (res_type == TN_RESOURCE_BUILDING_MAT)
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

    // Returning message about success.
    return sformat("Succesfully created object (id is %d).\n",
                   obj -> getObjectID());
}

//******************************************************************************
// `LIST` PROCESSOR.
//******************************************************************************

std::string CLI::list(std::stringstream& ss)
{
    std::string output;

    // Reading type.
    std::string type = "";
    ss >> type;

    // Listing visible objects.
    ObjectHeap* objs = this -> world -> getVisibleObjects();

    // Preparing begin and end iterators.
    ObjectHeap::const_iterator iter_begin, iter_end;
    if (type == "")
    {
        iter_begin = objs -> begin();
        iter_end   = objs -> end();
    }
    else if (type == TN_BUILDING)
    {
        iter_begin = objs -> begin(BUILDING);
        iter_end   = objs -> end(BUILDING);
    }
    else if (type == TN_CREATURE)
    {
        iter_begin = objs -> begin(CREATURE);
        iter_end   = objs -> end(CREATURE);
    }
    else if (type == TN_RESOURCE)
    {
        iter_begin = objs -> begin(RESOURCE);
        iter_end   = objs -> end(RESOURCE);
    }
    else if (type == TN_WEATHER)
    {
        iter_begin = objs -> begin(WEATHER);
        iter_end   = objs -> end(WEATHER);
    }
    else
    {
        return sformat("Error: unknown ObjectType (%s).\n", type.c_str());
    }

    ObjectHeap::const_iterator iter;
    for (iter = iter_begin; iter != iter_end; iter++)
    {
        Object* obj = *iter;

        // Preparing flags.
        std::string flags = "v";
        flags += obj -> isDestroyed() ? "d" : " ";
        flags += obj -> isImmortal() ? "i" : " ";
        flags += obj -> isSolid() ? "s" : "";

        // Printing output.
        output += sformat("%d\t%s\t%s\t(%f,\t%f)\n", obj -> getObjectID(),
                          flags.c_str(),
                          this -> obj_types[obj -> getType()].c_str(),
                          obj -> getCoords().getX(),
                          obj -> getCoords().getY());
    }

    return output;

    // TODO: Listing hidden objects.
    //ObjectHeap* hidden_objs = this -> world -> getHiddenObjects();
}

//******************************************************************************
// `INFO` PROCESSOR.
//******************************************************************************

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

    // Printing object type.
    ObjectType type = obj -> getType();
    output += sformat("Type\t\t\t%s\n", this -> obj_types[type].c_str());

    // Coordinates and angle.
    Vector v = obj -> getCoords();
    output += sformat("X\t\t\t%f\n", v.getX());
    output += sformat("Y\t\t\t%f\n", v.getY());
    output += sformat("Angle\t\t\t%f\n", obj -> getAngle());

    // Shape type.
    Shape shape = obj -> getShape();
    output += sformat("Shape\t\t\t%s (%f)\n",
                      this -> shape_types[shape.getType()].c_str(),
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
        output += "======== BUILDING INFORMATION ========\n";

        Building* building = dynamic_cast<Building*>(obj);

        // Free and max space.
        output += sformat("Free space\t\t%d/%d\n", building -> getFreeSpace(),
                          building -> getMaxSpace());

        // Completness.
        output += sformat("Is complete\t\t%s\n",
                          building -> getCompleteness() ? "yes" : "no");
    }
    else if (type == RESOURCE)
    {
        output += "======== RESOURCE INFORMATION ========\n";

        Resource* res = dynamic_cast<Resource*>(obj);

        // Mineability and restorability.
        output += sformat("Is mineable\t\t%s\n",
                          res -> isMineable() ? "yes" : "no");
        output += sformat("Is restorable\t\t%s\n",
                          res -> isRestorable() ? "yes" : "no");

        // Difficulty and progress.
        output += sformat("Difficulty\t\t%u\n", res -> getDifficulty());
        output += sformat("Progress\t\t%u\n", res -> getProgress());

        // Mining parameters.
        output += sformat("Steps to regeneration\t%u\n", res -> getStepsToReg());
        output += sformat("Regeneration amount\t%u\n", res -> getRegAmount());
        output += sformat("Amount per drop\t\t%u\n", res -> getAmountPerDrop());
    }
    else if (type == CREATURE)
    {
        output += "======== CREATURE INFORMATION ========\n";

        Creature* creat = dynamic_cast<Creature*>(obj);

        // Printing type.
        CreatureType subtype = creat -> getSubtype();
        output += sformat("Subtype\t\t\t%s\n",
                          this -> creat_types[subtype].c_str());

        // Printing age.
        output += sformat("Age\t\t\t%u/%u\n", creat -> getAge(),
                          creat -> getMaxAge());

        // Printing stats.
        output += sformat("Hunger\t\t\t%u/%u\n", creat -> getHunger(),
                          creat -> getMaxHunger());
        output += sformat("Sleepiness\t\t%u/%u\n", creat -> getSleepiness(),
                          creat -> getMaxSleepiness());
        output += sformat("Endurance\t\t%u/%u\n", creat -> getEndurance(),
                          creat -> getMaxEndurance());
        output += sformat("Force\t\t\t%u\n", creat -> getForce());

        // Printing decision.
        // FIXME: I use static cast there. Not good.
        CreatureAction act = static_cast<CreatureAction>(creat -> getCurrentDecision());
        output += sformat("Current decision\t%s\n",
                          this -> creat_acts[act].c_str());

        // Printing aim.
        const Object* aim = creat -> getAim();
        output += sformat("Aim ID\t\t\t%s\n", this -> printObjectID(aim).c_str());

        // Printing view area.
        Shape view_area = creat -> getViewArea();
        output += sformat("View area\t\t%s (%f)\n",
                          this -> shape_types[view_area.getType()].c_str(),
                          view_area.getSize());

        // Printing inventory.
        output += "Inventory\n";
        output += this -> printObjectHeap(creat -> getInventory());

        // Printing objects around.
        output += "Objects around\n";
        output += this -> printObjectHeap(creat -> getObjectsAround());

        if (subtype == HUMANOID)
        {
            output += "======== HUMANOID INFORMATION ========\n";

            Humanoid* hum = dynamic_cast<Humanoid*>(creat);

            // Printing ID.
            output += sformat("Humanoid ID\t\t%u\n", hum -> getHumanoidID());

            // Printing stats.
            output += sformat("Bravery\t\t\t%u\n", hum -> getBravery());
            output += sformat("Need in house\t\t%u\n", hum -> getNeedInHouse());

            // Printing home information.
            Building* home = hum -> getHome();
            output += sformat("Home ID\t\t\t%s\n", this -> printObjectID(home).c_str());

            // Printing visual memory.
            output += "Visual memory\n";
            output += this -> printObjectHeap(hum -> getVisMem());

            // Printing detailed act.
            output += sformat("Detailed action\t\t%s\n",
                              this -> hum_acts[hum -> getCurrentDetailedAct()].c_str());
        }
        else if (subtype == NON_HUMANOID)
        {
            output += "====== NON-HUMANOID INFORMATION ======\n";

            NonHumanoid* nhum = dynamic_cast<NonHumanoid*>(creat);
        }
    }

    return output;
}

//******************************************************************************
// `STEP` PROCESSOR.
//******************************************************************************

std::string CLI::step(std::stringstream& ss)
{
    uint amount = 1;
    ss >> amount;

    for (uint i = 0; i < amount; i++)
    {
        this -> control -> step();
    }

    return sformat("Successfully made %u steps.\n", amount);
}

//******************************************************************************
// `TRACE-STEP` PROCESSOR.
//******************************************************************************

std::string CLI::traceStep(std::stringstream& ss)
{
}

//******************************************************************************
// `CHANGE` PROCESSOR.
//******************************************************************************

std::string CLI::change(std::stringstream& ss)
{
}

//******************************************************************************
// HELPFULL METHODS.
//******************************************************************************

std::string CLI::printObjectHeap(const ObjectHeap* obj_heap, std::string indent,
                                 uint columns)
{
    std::string output;
    uint cur_column = 1;

    ObjectHeap::const_iterator iter;
    for (iter = obj_heap -> begin(); iter != obj_heap -> end(); iter++)
    {
        output += sformat("%s%d", indent.c_str(), (*iter) -> getObjectID());

        if (cur_column++ == columns || iter + 1 == obj_heap -> end())
        {
            cur_column = 1;
            output += "\n";
        }
    }

    return output;
}

std::string CLI::printObjectID(const Object* obj)
{
    if (obj == nullptr)
    {
        return "none";
    }

    return std::to_string(obj -> getObjectID());
}
