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

#define TN_CLUSTER_BUILDING_MAT     "fr"

#define TN_SHAPE_CIRCLE             "cr"
#define TN_SHAPE_SQUARE             "s"

#define TN_FIELD_CENTER             "center"
#define TN_FIELD_SHAPE              "shape"
#define TN_FIELD_SIZE               "size"
#define TN_FIELD_DANGER             "danger"

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
    this -> obj_types[RESOURCE] = "resource";
    this -> obj_types[BUILDING] = "building";
    this -> obj_types[TOOL]     = "tool    ";
    this -> obj_types[WEATHER]  = "weather ";
    this -> obj_types[CREATURE] = "creature";

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
    try
    {
        if (cmd == "init")          return this -> init(ss, false);
        if (cmd == "random-init")   return this -> init(ss, true);
        if (cmd == "generate")      return this -> generate(ss);
        if (cmd == "create")        return this -> create(ss);
        if (cmd == "list")          return this -> list(ss);
        if (cmd == "info")          return this -> info(ss);
        if (cmd == "change")        return this -> change(ss);
        if (cmd == "step")          return this -> step(ss);
        if (cmd == "trace-step")    return this -> traceStep(ss);
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
// `GENERATE` PROCESSOR.
//******************************************************************************

std::string CLI::generate(std::stringstream& ss)
{
    // Reading coordinates.
    double x;
    ss >> x;
    if (ss.fail())
    {
        return sformat("Error: x coordinate expected.\n") +
               sformat("Syntax: generate <x> <y> <type>\n");
    }

    double y;
    ss >> y;
    if (ss.fail())
    {
        return sformat("Error: y coordinate expected.\n") +
               sformat("Syntax: generate <x> <y> <type>\n");
    }

    // Reading type.
    std::string type;
    ss >> type;
    if (ss.fail())
    {
        return sformat("Error: ClusterType expected.\n") +
               sformat("Syntax: generate <x> <y> <type>\n");
    }

    if (type == TN_CLUSTER_BUILDING_MAT)
    {
        this -> world -> genForestAt(x, y);
    }
    else
    {
        return sformat("Error: unknown ClusterType. Possible values: %s.\n",
                       TN_CLUSTER_BUILDING_MAT);
    }

    return sformat("Successfully generated cluster (%s) at (%f, %f).\n",
                   type.c_str(), x, y);
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

std::string CLI::list(std::stringstream& ss, uint columns)
{
    // Reading type.
    std::string type = "";
    ss >> type;

    // Output.
    std::string output;

    for (uint k = 0; k < 2; k++)
    {
        ObjectHeap* objs = (k == 0 ? this -> world -> getVisibleObjects() :
                                     this -> world -> getHiddenObjects());

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

        // Listing objects.
        ObjectHeap::const_iterator iter;
        uint cur_column = 1;
        for (iter = iter_begin; iter != iter_end; iter++)
        {
            Object* obj = *iter;

            // Preparing flags.
            std::string flags = k == 0 ? "v" : "h";
            flags += obj -> isDestroyed() ? "d" : " ";
            flags += obj -> isImmortal() ? "i" : " ";
            flags += obj -> isSolid() ? "s" : " ";

            // Printing output.
            output += sformat("%d\t│ %s │ %s │ %f\t%f", obj -> getObjectID(),
                              flags.c_str(),
                              this -> obj_types[obj -> getType()].c_str(),
                              obj -> getCoords().getX(),
                              obj -> getCoords().getY());

            if (cur_column++ == columns)
            {
                output += "\n";
                cur_column = 1;
            }
            else
            {
                output += "\t\t║\t";
            }
        }
    }

    return output + "\n";
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
    Object* obj = this -> world -> getObjectByID(id);

    if (obj == nullptr)
    {
        return sformat("Error: object with id %u doesn't exist.\n", id);
    }

    return obj -> printObjectInfo() + "\n";
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
    // Reading id.
    uint id;
    ss >> id;
    if (ss.fail())
    {
        return sformat("Error: object id expected.\n") +
               sformat("Syntax: change <id> <field> <new_value>\n");
    }

    // Getting object.
    Object* obj = this -> world -> getObjectByID(id);
    if (obj == nullptr)
    {
        return sformat("Error: object with id %u doesn't exist.\n", id);
    }

    // Reading field name.
    std::string field;
    ss >> field;
    if (ss.fail())
    {
        return sformat("Error: field name expected.\n") +
               sformat("Syntax: change <id> <field> <new_value>\n");
    }

    if (field == TN_FIELD_CENTER)
    {
        double x, y;
        ss >> x >> y;
        if (!ss)
        {
            return sformat("Error: center coordinates expected.\n") +
                   sformat("Syntax: change <id> %s <x> <y>\n", TN_FIELD_SIZE);
        }

        obj -> setCoords(Vector(x, y));
    }
    else if (field == TN_FIELD_SIZE)
    {
        double size;
        ss >> size;
        if (!ss)
        {
            return sformat("Error: size expected.\n") +
                   sformat("Syntax: change <id> %s <size>\n", TN_FIELD_SIZE);
        }

        obj -> setShapeSize(size);
    }
    else if (field == TN_FIELD_SHAPE)
    {
        std::string shape;
        ss >> shape;
        if (!ss)
        {
            return sformat("Error: ShapeType expected.\n") +
                   sformat("Syntax: change <id> %s <ShapeType>\n",
                           TN_FIELD_SHAPE);
        }

        ShapeType type;
        if (shape == TN_SHAPE_CIRCLE)
        {
            type = CIRCLE;
        }
        else if (shape == TN_SHAPE_SQUARE)
        {
            type = SQUARE;
        }
        else
        {
            return sformat("Error: unknown ShapeType. Possible values: %s, %s.\n",
                           TN_SHAPE_CIRCLE, TN_SHAPE_SQUARE);
        }

        obj -> setShapeType(type);
    }
    else if (field == TN_FIELD_DANGER)
    {
        uint danger_level;
        ss >> danger_level;
        if (!ss)
        {
            return sformat("Error: uint expected.\n") +
                   sformat("Syntax: change <id> %s <danger>\n",
                           TN_FIELD_DANGER);
        }

        obj -> setDangerLevel(danger_level);
    }
    else
    {
        return sformat("Error: unknown FieldName.\n");
    }

    return "Successfully changed object.\n";
}

//******************************************************************************
// HELPFULL FUNCTIONS.
//******************************************************************************

template<class T> T read(std::stringstream& ss)
{
    T t;

    ss >> t;
    if (!ss)
    {
        // throw
    }

    return t;
}
