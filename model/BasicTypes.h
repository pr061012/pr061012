/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

/**
 * @file BasicTypes.h
 */

#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

/**
 * @brief For more shortness of the code.
 */
typedef unsigned int uint;

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
 * @enum  ActionType
 * @brief The ActionType enum. In some cases there are ids in parameters. These
 *        ids denote index of object in participants array. *Example*: action
 *        MINE, actor is Humanoid, participants are Resource (index is 0) and
 *        Tool (PICKAXE) (index is 1), parameters are res_id (= 0) and tool_id
 *        (= 1).
 */
enum ActionType
{
    /// @brief Description:     Move object to (x+delta_x, y+delta_y) point. \n
    ///        Actor:           Creature \n
    ///        Participants:    none \n
    ///        Parameters:      delta_x, delta_y
    GO,

    /// @brief Description:     Resource mining by tool. \n
    ///        Actor:           Humanoid \n
    ///        Participants:    Resource, Tool (PICKAXE) \n
    ///        Parameters:      res_id, tool_id
    MINE,

    /// @brief Description:     Repair building. \n
    ///        Actor:           Humanoid \n
    ///        Participants:    Building, Tool \n
    ///        Parameters:      building_id, tool_id
    REPAIR,

    /// @brief Description:     Harm one or more objects. \n
    ///        Actor:           Creature/Weather \n
    ///        Participants:    several objects \n
    ///        Parameters:      none
    HARM_OBJS,

    /// @brief Description:     Create object. \n
    ///        Actor:           Humanoid/Resource \n
    ///        Participants:    none \n
    ///        Parameters:
    ///                         * obj_type, x and y
    ///                         * for Resource creation: res_type, res_amount
    ///                         * for Tool creation: tool_type, mat_type
    ///                         * for Creature creation: creat_type
    CREATE_OBJ,

    /// @brief Description:     Drop objects to ground. \n
    ///        Actor:           Creature \n
    ///        Participants:    several objects \n
    ///        Parameters:      none
    DROP_OBJS,

    /// @brief Description:     Pick up objects from the ground. \n
    ///        Actor:           Creature \n
    ///        Participants:    several objects \n
    ///        Parameters:      none
    PICK_UP_OBJS
};

/**
 * @enum ActionState
 * @brief The ActionState enum
 */
enum ActionState
{
    /// Action is pending.
    PENDING,

    /// Action is failed (not allowed to do this action).
    FAILED,

    /// Action is succeeded (allowed to do this action).
    SUCCEEDED,

    /// @brief Action is not entirely succeeded (there were errors, but the part
    ///        of the action was done).
    SUCCEEDED_WITH_ERRORS
};

/**
 * @enum  ActionError
 * @brief The ActionError enum
 */
enum ActionError
{
    OBJ_IS_OUT_OF_RANGE,
    OBJ_IS_OUT_OF_VIEW,
    OBJ_IS_IMMORTAL,
    OBJ_IS_NOT_REPAIRABLE,
    OBJ_IS_NOT_MINEABLE,
    OBJ_IS_NOT_CREATABLE,
    OBJ_IS_NOT_PICKABLE
};

#endif // BASIC_TYPES_H
