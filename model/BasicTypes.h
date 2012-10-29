/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

/**
 * @brief The WeatherType enum
 */
enum WeatherType
{
    RAIN, CLOUDS, SNOW, HAIL, STORM, HURRICANE, EARTHQUAKE, METEOR_SHOWER
};

/**
 * @brief The ToolType enum
 */
enum ToolType
{
    SHOVEL, PICKAXE, SWORD, SHIELD, HOE, AXE, FISHING_ROD
};

/**
 * @brief The ResourceType enum
 */
enum ResourceType
{
    GOLD, SILVER, BRONZE, COAL, WOOD, BERRIES, IRON, STONE
};

/**
 * @brief The ObjectType enum
 */
enum ObjectType
{
    RESOURCE, TOOL, WEATHER, BUILDING, CREATURE
};

/**
 * @brief The ActionType enum
 */
enum ActionType
{
    // Special action (means that action isn't specified yet)
    NONE,

    // Common actions.
    SLEEP, EAT, BUILD, GATHER, RELAX, EXPLORE, COMMUNICATE, WORK, REALIZE_DREAM,
    DO_NOTHING
};

/**
 * @brief The CreatureType enum
 */
enum CreatureType 
{
	HUMANOID, NON_HUMANOID
};

#endif // BASIC_TYPES_H
