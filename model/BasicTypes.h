/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

/**
 * @enum ObjectType
 * @brief The ObjectType enum
 */
enum ObjectType
{
    RESOURCE, TOOL, WEATHER, BUILDING, CREATURE
};

/**
 * @enum WeatherType
 * @brief The WeatherType enum
 */
enum WeatherType
{
    RAIN, CLOUDS, SNOW, HAIL, STORM, HURRICANE, EARTHQUAKE, METEOR_SHOWER
};

/**
 * @enum ToolType
 * @brief The ToolType enum
 */
enum ToolType
{
    // Tools.
    SHOVEL, PICKAXE, HOE, FISHING_ROD,

    // Weapons.
    BOW, SWORD, SHIELD, AXE
};

/**
 * @enum ResourceType
 * @brief The ResourceType enum
 */
enum ResourceType
{
    // Mineable resources.
    BRONZE_ORE, IRON_ORE, SILVER_ORE, GOLD_ORE, WOOD,

    // Pickable resources.
    BRONZE, IRON, SILVER, GOLD, COAL, BERRIES, STONE

    // TODO: Add food.
};

/**
 * @enum CreatureAction
 * @brief The CreatureAction enum
 */
enum CreatureAction
{
    // Special action (means that action isn't specified yet)
    NONE,

    // Common actions.
    SLEEP, EAT, BUILD, GATHER, RELAX, EXPLORE, COMMUNICATE, WORK, REALIZE_DREAM,
    ESCAPE, CONTINUE_GENDER, DO_NOTHING
};

/**
 * @enum CreatureType
 * @brief The CreatureType enum
 */
enum CreatureType 
{
    HUMANOID, NON_HUMANOID
};

/**
 * @enum ActionType
 * @brief The ActionType enum
 */
enum ActionType
{
    GO, MINE, HARM_OBJ, HARM_OBJS, REPAIR, CREATE_OBJ, CREATE_OBJS, DROP_OBJ,
    DROP_OBJS, PICK_UP_OBJ, PICK_UP_OBJS
};

/**
 * @enum ActionState
 * @brief The ActionState enum
 */
enum ActionState
{
    PENDING, FAILED, SUCCEED
};

#endif // BASIC_TYPES_H
