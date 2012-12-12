/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "CLI.h"
#include "ECLIInvalidInput.h"

#include <cstdarg>
#include <sstream>

#include "../common/Vector/Vector.h"
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
#define TN_NHUM                     "nh"
#define TN_NHUM_COW                 "cow"
#define TN_NHUM_COW_DEMON           "0xDEADBEEF"
#define TN_NHUM_DRAGON              "dragon"
#define TN_BUILDING                 "b"
#define TN_RESOURCE                 "r"
#define TN_RESOURCE_WATER           "water"
#define TN_RESOURCE_GRASS           "grass"
#define TN_RESOURCE_BERRIES         "berries"
#define TN_RESOURCE_MEAT            "meat"
#define TN_RESOURCE_TREE            "tree"
#define TN_WEATHER                  "w"
#define TN_WEATHER_METEOR_SHOWER    "meteor-shower"
#define TN_WEATHER_RAIN             "rain"
#define TN_WEATHER_CLOUDS           "clouds"
#define TN_WEATHER_HURRICANE        "hurricane"

#define TN_CLUSTER_TREE             "forest"

#define TN_SHAPE_CIRCLE             "circle"
#define TN_SHAPE_SQUARE             "square"

#define TN_FIELD_CENTER             "center"
#define TN_FIELD_SHAPE              "shape"
#define TN_FIELD_SIZE               "size"
#define TN_FIELD_DANGER             "danger"
#define TN_FIELD_IMMORTALITY        "immortality"
#define TN_FIELD_SOLIDITY           "solidity"
#define TN_FIELD_DESTROYED          "destroyed"

#define TN_FIELD_AGE                "age"
#define TN_FIELD_ENDURANCE          "endurance"
#define TN_FIELD_HUNGER             "hunger"
#define TN_FIELD_HEALTH             "health"
#define TN_FIELD_SLEEPINESS         "sleepiness"
#define TN_FIELD_MAX_AGE            "mage"
#define TN_FIELD_MAX_DIRECTION      "mdirection"
#define TN_FIELD_MAX_ENDURANCE      "mendurance"
#define TN_FIELD_MAX_HUNGER         "mhunger"
#define TN_FIELD_MAX_HEALTH         "mhealth"
#define TN_FIELD_MAX_SLEEPINESS     "msleepiness"
#define TN_FIELD_FORCE              "force"

#define TN_FIELD_ACT                "a"
#define TN_A_NONE                   "none"
#define TN_A_SLEEP                  "sleep"
#define TN_A_EAT                    "eat"
#define TN_A_BUILD                  "build"
#define TN_A_GATHER                 "gather"
#define TN_A_COMMUNICATE            "communicate"
#define TN_A_WORK                   "work"
#define TN_A_REALIZE_DREAM          "realize-dream"
#define TN_A_ESCAPE                 "escape"
#define TN_A_DO_NOTHING             "do-nothing"

#define TN_FIELD_DET_ACT            "da"
#define TN_DA_HUNT                  "hunt"
#define TN_DA_TAKE_FOOD_FROM_INV    "inv-food"
#define TN_DA_FIND_FOOD             "find-food"
#define TN_DA_RELAX_AT_HOME         "home-relax"
#define TN_DA_SLEEP_AT_HOME         "home-sleep"
#define TN_DA_SLEEP_ON_THE_GROUND   "ground-sleep"
#define TN_DA_MINE_RESOURCES        "mine-res"
#define TN_DA_BUILD_HOUSE           "build-house"
#define TN_DA_CHOOSE_PLACE_FOR_HOME "choose-hplace"
#define TN_DA_FIGHT                 "fight"
#define TN_DA_RUN_FROM_DANGER       "run-from-danger"

//******************************************************************************
// STATIC FUNCTIONS.
//******************************************************************************

// Insolent copypaste:
// http://stackoverflow.com/a/8098080
static std::string sformat(const std::string& format, ...)
{
    uint size = 100;
    std::string result;
    va_list ap;

    while (true)
    {
        result.resize(size);

        va_start(ap, format);
        int n = vsnprintf((char *) result.c_str(), size, format.c_str(), ap);
        va_end(ap);

        if (n > -1 && n < (int) size)
        {
            result.resize((uint) n);
            break;
        }

        if (n > -1)
        {
            size = (uint) n + 1;
        }
        else
        {
            size *= 2;
        }
    }

    return result;
}

// Reads T from stringstream. Argument name is neaded for exception throwing
// (if failed).
template<class T> static T readFromSS(std::stringstream& ss, std::string arg_name) throw(ECLIInvalidInput)
{
    T t;

    ss >> t;
    if (!ss)
    {
        throw ECLIInvalidInput(arg_name + " expected");
    }

    return t;
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
    }
    catch(ECLIInvalidInput& exc)
    {
        return exc.what();
    }

    return sformat("Unknown command `%s`.\n", cmd.c_str());
}

//******************************************************************************
// `INIT` PROCESSOR.
//******************************************************************************

std::string CLI::init(std::stringstream &ss, bool random)
{
    // FIXME: Interpreting only one size.
    uint size = readFromSS<uint>(ss, "size");

    if (size < 50)
    {
        throw ECLIInvalidInput("size must be greater than 50");
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
    double x = readFromSS<double>(ss, "X coordinate");
    double y = readFromSS<double>(ss, "Y coordinate");

    // Reading type.
    std::string type = readFromSS<std::string>(ss, "ClusterType");

    if (type == TN_CLUSTER_TREE)
    {
        this -> world -> genForestAt(x, y);
    }
    else
    {
        throw ECLIInvalidInput("unknown ClusterType");
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
    double x = readFromSS<double>(ss, "X coordinate");
    double y = readFromSS<double>(ss, "Y coordinate");

    // Reading type.
    ObjectType obj_type;
    std::string type = readFromSS<std::string>(ss, "ObjectType");

    // Creating object.
    ParamArray pa;
    if (type == TN_CREATURE)
    {
        obj_type = CREATURE;

        std::string creat_type = readFromSS<std::string>(ss, "CreatureType");
        if (creat_type == TN_HUMANOID)
        {
            pa.addKey<CreatureType>("creat_type", HUMANOID);
        }
        else if (creat_type == TN_NHUM)
        {
            pa.addKey<CreatureType>("creat_type", NON_HUMANOID);
            std::string nhum_type = readFromSS<std::string>(ss, "NonHumanoidType");

            if (nhum_type == TN_NHUM_COW)
            {
                pa.addKey<NonHumanoidType>("nhum_type", COW);
            }
            else if (nhum_type == TN_NHUM_COW_DEMON)
            {
                pa.addKey<NonHumanoidType>("nhum_type", COW_DEMON);
            }
            else if (nhum_type == TN_NHUM_DRAGON)
            {
                pa.addKey<NonHumanoidType>("nhum_type", DRAGON);
            }
            else
            {
                throw ECLIInvalidInput("unknown NonHumanoidType");
            }
        }
        else
        {
            throw ECLIInvalidInput("unknown CreatureType");
        }
    }
    else if (type == TN_BUILDING)
    {
        obj_type = BUILDING;

        uint max_health = readFromSS<uint>(ss, "max health");
        uint max_space  = readFromSS<uint>(ss, "max space");

        pa.addKey<uint>("max_health", max_health);
        pa.addKey<uint>("max_space", max_space);
    }
    else if (type == TN_RESOURCE)
    {
        obj_type = RESOURCE;

        std::string res_type = readFromSS<std::string>(ss, "ResourceType");
        if (res_type == TN_RESOURCE_WATER)
        {
            pa.addKey<ResourceType>("res_type", WATER);
        }
        else if (res_type == TN_RESOURCE_GRASS)
        {
            pa.addKey<ResourceType>("res_type", GRASS);
        }
        else if (res_type == TN_RESOURCE_BERRIES)
        {
            pa.addKey<ResourceType>("res_type", BERRIES);
        }
        else if (res_type == TN_RESOURCE_MEAT)
        {
            pa.addKey<ResourceType>("res_type", MEAT);
        }
        else if (res_type == TN_RESOURCE_TREE)
        {
            pa.addKey<ResourceType>("res_type", TREE);
        }
        else
        {
            throw ECLIInvalidInput("unknown ResourceType");
        }

        uint res_amount = readFromSS<uint>(ss, "resource amount");
        pa.addKey<uint>("res_amount", res_amount);
    }
    else if (type == TN_WEATHER)
    {
        obj_type = WEATHER;

        std::string weat_type = readFromSS<std::string>(ss, "WeatherType");
        if (weat_type == TN_WEATHER_CLOUDS)
        {
            pa.addKey<WeatherType>("weat_type", CLOUDS);
        }
        else if (weat_type == TN_WEATHER_HURRICANE)
        {
            pa.addKey<WeatherType>("weat_type", HURRICANE);
        }
        else if (weat_type == TN_WEATHER_METEOR_SHOWER)
        {
            pa.addKey<WeatherType>("weat_type", METEOR_SHOWER);
        }
        else if (weat_type == TN_WEATHER_RAIN)
        {
            pa.addKey<WeatherType>("weat_type", RAIN);
        }
        else
        {
            throw ECLIInvalidInput("unknown WeatherType");
        }

        uint weat_steps = readFromSS<uint>(ss, "weather living steps");
        pa.addKey<uint>("weat_steps", weat_steps);
    }
    else
    {
        throw ECLIInvalidInput("unknown ObjectType");
    }

    // Creating object.
    ObjectFactory* obj_factory = this -> world -> getObjectFactory();
    Object* obj = obj_factory -> createObject(obj_type, pa);
    obj -> setCoords(Vector(x, y));
    this -> world -> addObject(true, obj);

    // Creating drop (for creatures).
    if (obj_type == CREATURE)
    {
        ParamArray drop_pa;
        drop_pa.addKey<ResourceType>("res_type", MEAT);
        Object* drop = obj_factory -> createObject(RESOURCE, drop_pa);
        this -> world -> addObject(false, drop);
        dynamic_cast<Creature*>(obj) -> getDropObjects() -> push(drop);
    }

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
                              obj -> getTypeName().c_str(),
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
    // Reading id.
    uint id = readFromSS<uint>(ss, "object ID");

    // Looking for object.
    Object* obj = this -> world -> getObjectByID(id);

    if (obj == nullptr)
    {
        throw ECLIInvalidInput("object with specified id doesn't exist");
    }

    return obj -> printObjectInfo(true) + "\n";
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
// `CHANGE` PROCESSOR.
//******************************************************************************

std::string CLI::change(std::stringstream& ss)
{
    // Reading id.
    uint id = readFromSS<uint>(ss, "object ID");

    // Getting object.
    Object* obj = this -> world -> getObjectByID(id);
    if (obj == nullptr)
    {
        throw ECLIInvalidInput("object with specified id doesn't exist");
    }

    std::string field = readFromSS<std::string>(ss, "field name");

    // Changing coordinates.
    if (field == TN_FIELD_CENTER)
    {
        double x = readFromSS<double>(ss, "X coordinate");
        double y = readFromSS<double>(ss, "Y coordinate");
        obj -> setCoords(Vector(x, y));
    }
    // Changing size.
    else if (field == TN_FIELD_SIZE)
    {
        double size = readFromSS<double>(ss, "size");
        obj -> setShapeSize(size);
    }
    // Changing shape.
    else if (field == TN_FIELD_SHAPE)
    {
        std::string shape = readFromSS<std::string>(ss, "ShapeType");

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
            throw ECLIInvalidInput("unknown ShapeType");
        }

        obj -> setShapeType(type);
    }
    // Changing danger.
    else if (field == TN_FIELD_DANGER)
    {
        uint danger_level = readFromSS<uint>(ss, "danger level");
        obj -> setDangerLevel(danger_level);
    }
    // Immortality.
    else if (field == TN_FIELD_IMMORTALITY)
    {
        uint immortality = readFromSS<uint>(ss, "immortality");
        if (immortality) obj -> makeImmortal(); else obj -> makeMortal();
    }
    // Solidity.
    else if (field == TN_FIELD_SOLIDITY)
    {
        uint solidity = readFromSS<uint>(ss, "solidity");
        if (solidity) obj -> makeSolid(); else obj -> makeNonSolid();
    }
    // Changing creature params.
    else if (obj -> getType() == CREATURE)
    {
        Creature* creat = dynamic_cast<Creature*>(obj);

        if (field == TN_FIELD_AGE)
        {
            uint age = readFromSS<uint>(ss, "age");
            creat -> setAge(age);
        }
        else if (field == TN_FIELD_MAX_AGE)
        {
            uint max_age = readFromSS<uint>(ss, "max age");
            creat -> setMaxAge(max_age);
        }
        else if (field == TN_FIELD_ENDURANCE)
        {
            uint endurance = readFromSS<uint>(ss, "endurance");
            creat -> setEndurance(endurance);
        }
        else if (field == TN_FIELD_MAX_ENDURANCE)
        {
            uint max_endurance = readFromSS<uint>(ss, "max endurance");
            creat -> setMaxEndurance(max_endurance);
        }
        else if (field == TN_FIELD_HUNGER)
        {
            uint hunger = readFromSS<uint>(ss, "hunger");
            creat -> setHunger(hunger);
        }
        else if (field == TN_FIELD_MAX_HUNGER)
        {
            uint max_hunger = readFromSS<uint>(ss, "max hunger");
            creat -> setMaxHunger(max_hunger);
        }
        else if (field == TN_FIELD_HEALTH)
        {
            uint health = readFromSS<uint>(ss, "health");
            creat -> setHealth(health);
        }
        else if (field == TN_FIELD_MAX_HEALTH)
        {
            uint max_health = readFromSS<uint>(ss, "max health");
            creat -> setMaxHealth(max_health);
        }
        else if (field == TN_FIELD_SLEEPINESS)
        {
            uint sleepiness = readFromSS<uint>(ss, "sleepiness");
            creat -> setSleepiness(sleepiness);
        }
        else if (field == TN_FIELD_MAX_SLEEPINESS)
        {
            uint max_sleepiness = readFromSS<uint>(ss, "max sleepiness");
            creat -> setMaxSleepiness(max_sleepiness);
        }
        else if (field == TN_FIELD_FORCE)
        {
            uint force = readFromSS<uint>(ss, "force");
            creat -> setForce(force);
        }
        else if (field == TN_FIELD_ACT)
        {
            std::string act = readFromSS<std::string>(ss, "creature action");
            if (act == TN_A_BUILD)              creat -> setCurrentAction(BUILD);
            else if (act == TN_A_COMMUNICATE)   creat -> setCurrentAction(COMMUNICATE);
            else if (act == TN_A_DO_NOTHING)    creat -> setCurrentAction(DO_NOTHING);
            else if (act == TN_A_EAT)           creat -> setCurrentAction(EAT);
            else if (act == TN_A_ESCAPE)        creat -> setCurrentAction(ESCAPE);
            else if (act == TN_A_GATHER)        creat -> setCurrentAction(GATHER);
            else if (act == TN_A_NONE)          creat -> setCurrentAction(NONE);
            else if (act == TN_A_REALIZE_DREAM) creat -> setCurrentAction(REALIZE_DREAM);
            else if (act == TN_A_SLEEP)         creat -> setCurrentAction(SLEEP);
            else if (act == TN_A_WORK)          creat -> setCurrentAction(WORK);
        }
        else if (creat -> getSubtype() == HUMANOID)
        {
            Humanoid* hum = dynamic_cast<Humanoid*>(creat);

            if (field == TN_FIELD_DET_ACT)
            {
                std::string detailed_act = readFromSS<std::string>(ss, "humanoid detailed action");
                if (detailed_act == TN_DA_BUILD_HOUSE)                hum -> setDetailedAction(BUILD_HOUSE);
                else if (detailed_act == TN_DA_CHOOSE_PLACE_FOR_HOME) hum -> setDetailedAction(CHOOSE_PLACE_FOR_HOME);
                else if (detailed_act == TN_DA_FIGHT)                 hum -> setDetailedAction(FIGHT);
                else if (detailed_act == TN_DA_FIND_FOOD)             hum -> setDetailedAction(FIND_FOOD);
                else if (detailed_act == TN_DA_HUNT)                  hum -> setDetailedAction(HUNT);
                else if (detailed_act == TN_DA_MINE_RESOURCES)        hum -> setDetailedAction(MINE_RESOURSES);
                else if (detailed_act == TN_DA_RELAX_AT_HOME)         hum -> setDetailedAction(RELAX_AT_HOME);
                else if (detailed_act == TN_DA_RUN_FROM_DANGER)       hum -> setDetailedAction(RUN_FROM_DANGER);
                else if (detailed_act == TN_DA_SLEEP_AT_HOME)         hum -> setDetailedAction(SLEEP_AT_HOME);
                else if (detailed_act == TN_DA_SLEEP_ON_THE_GROUND)   hum -> setDetailedAction(SLEEP_ON_THE_GROUND);
                else if (detailed_act == TN_DA_TAKE_FOOD_FROM_INV)    hum -> setDetailedAction(TAKE_FOOD_FROM_INVENTORY);
                else
                {
                    throw ECLIInvalidInput("unknown detailed action for Humanoid");
                }
            }
            else
            {
                throw ECLIInvalidInput("unknown field name for Humanoid");
            }
        }
        else
        {
            throw ECLIInvalidInput("unknown field name for Creature");
        }
    }
    // Unknown field name.
    else
    {
        throw ECLIInvalidInput("unknown field name");
    }

    return "Successfully changed object.\n";
}
