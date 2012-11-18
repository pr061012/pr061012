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

//******************************************************************************
// SHAPE.
//******************************************************************************

/**
 * @enum  ShapeType
 * @brief The ShapeType enum
 */
enum ShapeType
{
    CIRCLE, SQUARE
};

//******************************************************************************
// OBJECTS TYPES.
//******************************************************************************

/**
 * @enum ObjectType
 * @brief The ObjectType enum
 *
 *        *NOTE*: Don't forget to increase AMNT_OBJECT_TYPES while adding new
 *                action types!
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
    // FIXME: Silly dummy.
    RES_FOOD, RES_BUILDING_MAT,

    // Mineable resources.
    BRONZE_ORE, IRON_ORE, SILVER_ORE, GOLD_ORE, WOOD,

    // Pickable resources.
    BRONZE, IRON, SILVER, GOLD, COAL, BERRIES, STONE,

    // TODO: Add food.
    GRASS
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
 * @enum NonHumanoidType
 * @brief The NonHumanoidType enum
 */
enum NonHumanoidType
{
    COW, BEAR, DRAGON, GOOSE, SHEEP
};

//******************************************************************************
// CREATURE.
//******************************************************************************

/**
 * @enum SpeedType
 * @brief The SpeedType enum
 */
enum SpeedType
{
    SLOW_SPEED, FAST_SPEED
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
 * @enum DetailedHumAction
 * @brief The DetailedHumAction enum
 */
enum DetailedHumAction
{
    // EAT actions.
    HUNT, TAKE_FOOD_FROM_INVENTORY, FIND_FOOD,

    // RELAX actions
    RELAX_AT_HOME,

    // SLEEP ations
    SLEEP_AT_HOME, SLEEP_ON_THE_GROUND,

    // BUILD actions
    MINE_RESOURSES, BUILD_HOUSE, CHOOSE_PLACE_FOR_HOME,

    // ESCAPE actions
    FIGHT, RUN_FROM_DANGER
};

//******************************************************************************
// ACTION.
//******************************************************************************

/**
 * @enum  ActionType
 * @brief The ActionType enum. In some cases there are ids in parameters. These
 *        index denote index of object in participants array. *Example*: action
 *        MINE, actor is Humanoid, participants are Resource (index is 0) and
 *        Tool (PICKAXE) (index is 1), parameters are res_index (= 0) and
 *        tool_index (= 1).
 *
 *        *NOTE*: Don't forget to increase AMNT_ACTION_TYPES while adding new
 *                action types!
 */
enum ActionType
{
    /// @brief Description:     Object goes to to another point (direction is
    ///                         set by angle). \n
    ///        Actor:           Creature/Weather \n
    ///        Participants:    none \n
    ///        Parameters:      angle (*double*), speed (*SpeedType*)
    GO,

    /// @brief Description:     Object moves another object. \n
    ///        Actor:           Humanoid \n
    ///        Participants:    Object \n
    ///        Parameters:      angle (*double*), speed (*SpeedType*)
    MOVE,

    /// @brief Description:     Resource mining by tool. \n
    ///        Actor:           Humanoid \n
    ///        Participants:    Resource, Tool (PICKAXE) \n
    ///        Parameters:      res_index (*uint*), tool_index (*uint*)
    MINE_OBJ,

    /// @brief Description:     Regenerate object. \n
    ///        Actor:           Humanoid/Resource \n
    ///        Participants:    Object, Tool \n
    ///        Parameters:      object_index (*uint*), tool_index (*uint*)
    REGENERATE_OBJ,

    /// @brief Description:     Harm one or more objects. \n
    ///        Actor:           Creature/Weather \n
    ///        Participants:    Tool (Creature only, optional),
    ///                         several objects \n
    ///        Parameters:      tool_index (*uint*)
    HARM_OBJS,

    /// @brief Description:     Create object. \n
    ///        Actor:           Humanoid/Resource \n
    ///        Participants:    none \n
    ///        Parameters:
    ///                         * obj_type (*ObjectType*), x (*uint*) and y
    ///                           (*uint*)
    ///                         * for Resource creation: res_type
    ///                           (*ResourceType*), res_amount (*uint*)
    ///                         * for Tool creation: tool_type (*ToolType*),
    ///                           mat_type (*uint*)
    ///                         * for Creature creation: creat_type
    ///                           (*CreatureType*)
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
    PICK_UP_OBJS,

    /// @brief Description:     Object eats object. \n
    ///        Actor:           NonHumanoid \n
    ///        Participants:    Resource \n
    ///        Parameters:      none \n
    EAT_OBJ
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
    NO_ERROR,
    OBJ_IS_OUT_OF_RANGE,
    OBJ_IS_OUT_OF_VIEW,
    OBJ_IS_IMMORTAL,
    OBJ_IS_NOT_REPAIRABLE,
    OBJ_IS_NOT_MINEABLE,
    OBJ_IS_NOT_CREATABLE,
    OBJ_IS_NOT_PICKABLE,
    OBJ_IS_NOT_MOVEABLE,
    OBJ_IS_STUCK,
    OBJ_CANT_PICKUP,
    OBJ_CANT_DROP,
    OBJ_IS_NOT_IN_HEAP,
    OBJ_CANT_EAT,
    TOO_MANY_PARTICIPANTS,
    OBJ_IS_NOT_EATABLE
};

//******************************************************************************
// MESSAGE.
//******************************************************************************

/**
 * @enum  MessageType
 * @brief The MessageType enum
 */
enum MessageType
{
    UNDER_ATTACK
};

#endif // BASIC_TYPES_H
