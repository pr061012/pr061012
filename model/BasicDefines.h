/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

/**
 * @file BasicTypes.h
 */
 
#ifndef BASIC_DEFINES_H
#define BASIC_DEFINES_H

//******************************************************************************
// TIME DEFINES.
// Prefix: TM.
//******************************************************************************

/// Amount of controller ticks (which change the world) in one second.
#define TM_TICKS_PER_SECOND     32

//******************************************************************************
// SIZE DEFINES.
// Prefix: SZ.
//******************************************************************************

/// Humanoid size.
#define SZ_HUMANOID_DIAMETER    (double) 1

/// Building side (minimum size).
#define SZ_BUILDING_SIDE_MIN    3 * SZ_HUMANOID_DIAMETER

/// Building side (maximum size).
#define SZ_BUILDING_SIDE_MAX    10 * SZ_HUMANOID_DIAMETER

//******************************************************************************
// WEATHER DEFINES.
// Prefix: WEAT.
//******************************************************************************

/// Minimum amount of living steps for weather.
#define WEAT_STEPS_MIN      3200
/// Maximum amount of living steps for weather.
#define WEAT_STEPS_MAX      6400

//******************************************************************************
// TOOL DEFINES.
// Prefix: TOOL.
// These defines describes value of tool's max strength. They are defined there
// for each mine resource type, for list of them look for BasicTypes.h file
// (ResourceType enum).
//******************************************************************************

#define TOOL_STONE_STRENGTH     100
#define TOOL_BRONZE_STRENGTH    200
#define TOOL_IRON_STRENGTH      400
#define TOOL_SILVER_STRENGTH    800
#define TOOL_GOLD_STRENGTH      1600

//******************************************************************************
// RESOURCE DEFINES.
// Prefix: RES.
//******************************************************************************

// Regeneration rate (amount of world steps to regenerate).
#define RES_REGENERATION_RATE       160

// Ranges of amount of resource.

#define RES_WOOD_AMOUNT_MIN         10
#define RES_WOOD_AMOUNT_MAX         20

#define RES_BRONZE_ORE_AMOUNT_MIN   50
#define RES_BRONZE_ORE_AMOUNT_MAX   60

#define RES_IRON_ORE_AMOUNT_MIN     50
#define RES_IRON_ORE_AMOUNT_MAX     60

#define RES_SILVER_ORE_AMOUNT_MIN   30
#define RES_SILVER_ORE_AMOUNT_MAX   40

#define RES_GOLD_ORE_AMOUNT_MIN     10
#define RES_GOLD_ORE_AMOUNT_MAX     20

// Amount of resource to regenerate on each regeneration step.

#define RES_WOOD_REG_AMOUNT         2
#define RES_BRONZE_ORE_REG_AMOUNT   3
#define RES_IRON_ORE_REG_AMOUNT     3
#define RES_SILVER_ORE_REG_AMOUNT   2
#define RES_GOLD_ORE_REG_AMOUNT     1

// Amount of steps to mine resource.

#define RES_WOOD_DIFFICULTY         16
#define RES_BRONZE_ORE_DIFFICULTY   32
#define RES_IRON_ORE_DIFFICULTY     48
#define RES_SILVER_ORE_DIFFICULTY   64
#define RES_GOLD_ORE_DIFFICULTY     80

// Ranges of amount of resource what will drop at each mining.

#define RES_WOOD_DROP_MIN           1
#define RES_WOOD_DROP_MAX           3

#define RES_BRONZE_ORE_DROP_MIN     10
#define RES_BRONZE_ORE_DROP_MAX     15

#define RES_IRON_ORE_DROP_MIN       10
#define RES_IRON_ORE_DROP_MAX       15

#define RES_SILVER_ORE_DROP_MIN     5
#define RES_SILVER_ORE_DROP_MAX     10

#define RES_GOLD_ORE_DROP_MIN       3
#define RES_GOLD_ORE_DROP_MAX       8

//******************************************************************************
// CREATURE DEFINES.
// Prefix: CREAT.
//******************************************************************************

// Values of these coeffiecients should lay in range [CREAT_*_MIN, CREAT_*_MAX].

/// Minimum possible value of max_health.
#define CREAT_HEALTH_MIN      50
/// Maximum possible value of max_health.
#define CREAT_HEALTH_MAX      100

/// Minimum possible value of max_satiety.
#define CREAT_HUNGER_MIN      50
/// Maximum possible value of max_satiety
#define CREAT_HUNGER_MAX      100

/// Minimum possible value of max_sleepiness.
#define CREAT_SLEEPINESS_MIN  50
/// Maximum possible value of max_sleepiness.
#define CREAT_SLEEPINESS_MAX  100

/// Amount of steps before updates basic attrs for creature.
#define CREAT_STEPS           150
/// Amount of steps before updates safety
#define CREAT_SAFETY_STEPS    16
/// Amount of steps before updates need_in_descendants.
#define CREAT_DESC_STEPS      1500
/// Amount of steps before updates age.
#define CREAT_AGE_STEPS       5000 //it is taken from my ceiling

/// Changes of hunger for one step
#define CREAT_DELTA_HUNGER    2
/// Changes of sleepiness for one step
#define CREAT_DELTA_SLEEP     1

/// When delta is more than this const, creature makes new decision
#define CREAT_CRIT_CONST  50

//******************************************************************************
// CREATURES ATTRIBUTES DEFINES.
// Prefix: ATTR.
//******************************************************************************

/// Attribute hunger
#define ATTR_HUNGER              0
/// Attribute sleepiness
#define ATTR_SLEEPINESS          1
/// Attribute need_in_house
#define ATTR_NEED_IN_HOUSE       2
/// Attribute need in points
#define ATTR_NEED_IN_POINTS      3
/// Attribute laziness
#define ATTR_LAZINESS            4
/// Attribute health
#define ATTR_HEALTH              5
/// Attribute communication
#define ATTR_COMMUNICATION       6
/// Attribute safety
#define ATTR_SAFETY              7
/// Attribute need in descendant
#define ATTR_NEED_IN_DESC        8

//******************************************************************************
// HUMANOID'S DEFINES.
// Prefix: HUM.
//******************************************************************************

// Values of these coeffiecients should lay in range [HUM_*_MIN, HUM_*_MAX].

/// Minimum possible value of humanoid's max_age.
#define HUM_AGE_MIN         40
/// Maximum possible value of humanoid's max_age.
#define HUM_AGE_MAX         50

/// Minimum possible value of humanoid's max_sociability.
#define HUM_SOCIABILITY_MIN 0
/// Maximum possible value of humanoid's max_sociability.
#define HUM_SOCIABILITY_MAX 100

/// Minimum possible value of humanoid's diligence.
#define HUM_LAZINESS_MIN    0
/// Maximum possible value of humanoid's diligence.
#define HUM_LAZINESS_MAX    100

/// Changes of need in descendant for one step
#define HUM_DELTA_NEED_IN_DESC    1
/// Changes of sociability for one step
#define HUM_DELTA_SOC             1

//******************************************************************************
// NONHUMANOID'S DEFINES.
// Prefix: NHUM.
//******************************************************************************

// Values of these coeffiecients should lay in range [NHUM_*_MIN, NHUM_*_MAX].

/// Minimum possible value of non-humanoid's max_age.
#define NHUM_AGE_MIN        10
/// Maximum possible value of non-humanoid's max_age.
#define NHUM_AGE_MAX        20

/// Changes of need_in_descendant for one step
#define NHUM_DELTA_NEED_IN_DESC   2

/// Amount of steps to decrease sleepiness
#define NHUM_DECR_SLEEP_STEPS     100

#endif // BASIC_DEFINES_H
