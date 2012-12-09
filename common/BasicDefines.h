/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

/**
 * @file BasicDefines.h
 */

#ifndef BASIC_DEFINES_H
#define BASIC_DEFINES_H

#include "BasicTypes.h"

//******************************************************************************
// TIME DEFINES.
// Prefix: TM.
//******************************************************************************

/// Amount of controller ticks (which change the world) in one second.
#define TM_TICKS_PER_SECOND         32

//******************************************************************************
// VIEW DEFINES.
// Prefix: VIEW.
//******************************************************************************

#define VIEW_SCREEN_WIDTH           800
#define VIEW_SCREEN_HEIGHT          600

/// Aspect ratio of the screen
#define VIEW_ASPECT_RATIO           ((double) VIEW_SCREEN_HEIGHT / VIEW_SCREEN_WIDTH)

/// Radius of field of view of game camera
#define VIEW_CAM_RADIUS             20

/// Radius in which objects are checked for cursor click (in-game coordinates)
#define VIEW_CURSOR_RAD             (double) 1

/// Size of grid cells relative to the default value.
/// Default is VIEW_CAM_RADIUS/8 game units of length
#define VIEW_GRID_SIZE              (double) 4

/// Defines the default value of TextField top margin, relative to the font size.
#define VIEW_TXT_TOP_MARGIN         0.25

//******************************************************************************
// SIZE DEFINES.
// Prefix: SZ.
//******************************************************************************

/// Humanoid size.
#define SZ_HUM_DIAM                 (double) 1

// TODO: Add sizes for different types of NonHums.
/// Cow size.
#define SZ_NHUM_COW_DIAM            SZ_HUM_DIAM * 0.5
/// Dragon size.
#define SZ_NHUM_DRAGON_DIAM         SZ_HUM_DIAM * 2.5

/// World size (vertical side).
#define SZ_WORLD_VSIDE              100 * SZ_HUM_DIAM
/// World size (horizontal size).
#define SZ_WORLD_HSIDE              100 * SZ_HUM_DIAM

/// Default size for everything.
#define SZ_DEFAULT                  SZ_HUM_DIAM

/// Coefficient for reach area size.
#define SZ_REACH_AREA_COEF          1.3

/// Building side (minimum size).
#define SZ_BUILDING_SIDE_MIN        3 * SZ_HUM_DIAM
/// Building side (maximum size).
#define SZ_BUILDING_SIDE_MAX        3 * SZ_HUM_DIAM

/// Meteor shower's shape diameter (minimum size).
#define SZ_WEAT_METEOR_SHOWER_DIAM_MIN  4 * SZ_HUM_DIAM
/// Meteor shower's shape diameter (maximum size).
#define SZ_WEAT_METEOR_SHOWER_DIAM_MAX  5 * SZ_HUM_DIAM
/// Clouds' shape diameter (minimum size).
#define SZ_WEAT_CLOUDS_DIAM_MIN     10 * SZ_HUM_DIAM
/// Clouds' shape diameter (maximum size).
#define SZ_WEAT_CLOUDS_DIAM_MAX     20 * SZ_HUM_DIAM
/// Rain's shape diameter (minimum size).
#define SZ_WEAT_RAIN_DIAM_MIN       10 * SZ_HUM_DIAM
/// Rain's shape diameter (maximum size).
#define SZ_WEAT_RAIN_DIAM_MAX       20 * SZ_HUM_DIAM
/// Hurricane's shape diameter (minimum size).
#define SZ_WEAT_HURRICANE_DIAM_MIN  7 * SZ_HUM_DIAM
/// Hurricane's shape diameter (maximum size).
#define SZ_WEAT_HURRICANE_DIAM_MAX  7 * SZ_HUM_DIAM

/// Water's shape diameter (minimum size).
#define SZ_RES_WATER_DIAM_MIN       5 * SZ_HUM_DIAM
/// Water's shape diameter (maximum size).
#define SZ_RES_WATER_DIAM_MAX       7 * SZ_HUM_DIAM
/// Grass' shape diameter (minimum size).
#define SZ_RES_GRASS_DIAM_MIN       5 * SZ_HUM_DIAM
/// Grass' shape diameter (maximum size).
#define SZ_RES_GRASS_DIAM_MAX       7 * SZ_HUM_DIAM
/// Berries' shape diameter (minimum size).
#define SZ_RES_BERRIES_DIAM_MIN     0.5 * SZ_HUM_DIAM
/// Berries' shape diameter (maximum size).
#define SZ_RES_BERRIES_DIAM_MAX     0.9 * SZ_HUM_DIAM
/// Meat's shape diameter (minimum size).
#define SZ_RES_MEAT_DIAM_MIN        0.5 * SZ_HUM_DIAM
/// Meat's shape diameter (maximum size).
#define SZ_RES_MEAT_DIAM_MAX        0.9 * SZ_HUM_DIAM
/// Tree's shape diameter (minimum size).
#define SZ_RES_TREE_DIAM_MIN        2 * SZ_HUM_DIAM
/// Tree's shape diameter (maximum size).
#define SZ_RES_TREE_DIAM_MAX        3 * SZ_HUM_DIAM

/// Tool size (when dropped to ground).
#define SZ_TOOL_DIAM                SZ_HUM_DIAM * 0.1

/// View area for NonHumanoid.
#define SZ_NHUM_VIEW_DIAM           50 * SZ_HUM_DIAM

/// View area for Humanoid.
#define SZ_HUM_VIEW_DIAM            50 * SZ_HUM_DIAM

//******************************************************************************
// SHAPE DEFINES.
// Prefix: SHP.
//******************************************************************************

/// Default shape for everything.
#define SHP_DEFAULT                 CIRCLE

/// Humanoid's shape.
#define SHP_HUMANOID                CIRCLE

/// NonHumanoid's shape.
#define SHP_NHUM                    CIRCLE

/// Building's shape.
#define SHP_BUILDING                SQUARE

/// Weather's shape.
#define SHP_WEATHER                 CIRCLE

/// Resource's shape.
#define SHP_RESOURCE                CIRCLE

/// Tool's shape.
#define SHP_TOOL                    CIRCLE

/// Humanoid view area shape.
#define SHP_HUM_VIEW_TYPE           CIRCLE

/// NonHumanoid view area shape.
#define SHP_NHUM_VIEW_TYPE          CIRCLE

//******************************************************************************
// DANGER DEFINES.
// Prefix: DNGR.
//******************************************************************************

/// Humanoid's danger level.
#define DNGR_HUMANOID               5

/// Cow's s danger level.
#define DNGR_NHUM_COW               1
/// Dragon's s danger level.
#define DNGR_NHUM_DRAGON            15

/// Resource's danger level.
#define DNGR_RESOURCE               0

/// Meteor shower's danger level.
#define DNGR_WEATHER_METEOR_SHOWER  25
/// Rain's danger level.
#define DNGR_WEATHER_RAIN           0
/// Clouds' danger level.
#define DNGR_WEATHER_CLOUDS         0
/// Hurricane's danger level.
#define DNGR_WEATHER_HURRICANE      25

/// Building's danger level.
#define DNGR_BUILDING               0

//******************************************************************************
// WEIGHT DEFINES.
// Prefix: WGHT.
//******************************************************************************

/// Humanoid's weight.
#define WGHT_HUMANOID               50

// TODO: Different values for different types of NonHumanoid.
/// Cow's weight.
#define WGHT_NHUM_COW               30
/// Dragon's weight.
#define WGHT_NHUM_DRAGON            250

// TODO: Different values for different types of Resource.
/// Resource's weight.
#define WGHT_RESOURCE               1

// TODO: Different values for different types of Weather.
/// Weather's weight.
#define WGHT_WEATHER                1000

/// Building's weight.
#define WGHT_BUILDING               400

//******************************************************************************
// SPEED DEFINES.
// Prefix: SPD.
//******************************************************************************

// Coefficient for calculation of slow speed.
#define SPD_SLOW_SPEED_COEF         1

// Coefficient for calculation of fast speed.
#define SPD_FAST_SPEED_COEF         1.8

// Humanoid's normal speed.
#define SPD_HUM                     (SZ_HUM_DIAM * 5 / TM_TICKS_PER_SECOND)

// Cow's normal speed.
#define SPD_NHUM_COW                (SZ_NHUM_COW_DIAM * 5 / TM_TICKS_PER_SECOND)
// Dragon's normal speed.
#define SPD_NHUM_DRAGON             (SZ_NHUM_DRAGON_DIAM * 2 / TM_TICKS_PER_SECOND)

/// Meteor shower's normal speed.
#define SPD_WEATHER_METEOR_SHOWER   (SPD_NHUM_COW / 2)
/// Clouds's normal speed.
#define SPD_WEATHER_CLOUDS          (SPD_NHUM_COW / 4)
/// Rain's normal speed.
#define SPD_WEATHER_RAIN            (SPD_NHUM_COW / 2)
/// Hurricane's normal speed.
#define SPD_WEATHER_HURRICANE       SPD_HUM

//******************************************************************************
// GENERATION DEFINES.
// Prefix: GEN.
//******************************************************************************

/// @brief Linear decrease of tree gen probability as tree generation goes
///        further from forest center (initial is 1.0 == 100%).
#define GEN_TREE_PROB_DECAY         0.1

/// Interval in distance of trees generation.
#define GEN_TREE_INTERVAL           1.1 * SZ_RES_TREE_DIAM_MAX

//******************************************************************************
// OBJECT DEFINES.
// Prefix: OBJ.
//******************************************************************************

/// Indentation for second column in object information.
#define OBJ_INFO_INDENT             25

//******************************************************************************
// WEATHER DEFINES.
// Prefix: WEAT.
//******************************************************************************

/// Minimum amount of living steps for weather.
#define WEAT_STEPS_MIN              180 * TM_TICKS_PER_SECOND
/// Maximum amount of living steps for weather.
#define WEAT_STEPS_MAX              300 * TM_TICKS_PER_SECOND

/// Weather's roaming steps (steps before roam direction changing).
#define WEAT_ROAM_STEPS             30 * TM_TICKS_PER_SECOND

/// Weather's action steps (steps before generating new weather action).
#define WEAT_ACTION_STEPS           (TM_TICKS_PER_SECOND / 4)

/// Coefficient of hurricane's twisting force. Value should lie in range [1, 2].
#define WEAT_HURRICANE_TWIST_COEF   1.5

//******************************************************************************
// TOOL DEFINES.
// Prefix: TOOL.
// These defines describes value of tool's max strength. They are defined there
// for each mine resource type, for list of them look for BasicTypes.h file
// (ResourceType enum).
//******************************************************************************

/// Stone tool strength.
#define TOOL_STONE_STRENGTH         100

#define TOOL_BRONZE_STRENGTH        200
/// Iron tool strength.
#define TOOL_IRON_STRENGTH          400
/// Silver tool strength.
#define TOOL_SILVER_STRENGTH        800
/// Gold tool strength.
#define TOOL_GOLD_STRENGTH          1600

//******************************************************************************
// RESOURCE DEFINES.
// Prefix: RES.
//******************************************************************************

// Regeneration rate (amount of world steps to regenerate).
#define RES_REGENERATION_RATE       160

// Ranges of amount of resource.

#define RES_TREE_AMOUNT_MIN         10
#define RES_TREE_AMOUNT_MAX         20

#define RES_GRASS_AMOUNT_MIN        300
#define RES_GRASS_AMOUNT_MAX        500

#define RES_BERRIES_AMOUNT_MIN      20
#define RES_BERRIES_AMOUNT_MAX      40

#define RES_MEAT_AMOUNT_MIN         15
#define RES_MEAT_AMOUNT_MAX         25

// Amount of resource to regenerate on each regeneration step.

#define RES_TREE_REG_AMOUNT         2

// Amount of steps to mine resource.

#define RES_DEFAULT_DIFFICULTY      1
#define RES_TREE_DIFFICULTY         16

// Ranges of amount of resource what will drop at each mining.

#define RES_TREE_DROP_MIN           1
#define RES_TREE_DROP_MAX           3

// Food values
#define RES_GRASS_FOOD_VALUE        1
#define RES_BERRIES_FOOD_VALUE      2
#define RES_MEAT_FOOD_VALUE         5
#define RES_FOOD_VALUE              3

//******************************************************************************
// BUILDING DEFINES
// Prefix: BLD.
//******************************************************************************

// Range for building max health.
#define BLD_MAX_HEALTH_MIN          100
#define BLD_MAX_HEALTH_MAX          150

/// Building completeness coefficient.
#define BLD_COMPLETENESS_COEF       0.8

// Range for building max space.
#define BLD_MAX_SPACE_MIN           100
#define BLD_MAX_SPACE_MAX           150

//******************************************************************************
// DAMAGE DEFINES
// Prefix: DMG.
//******************************************************************************

#define DMG_FORCE_MIN               10
#define DMG_FORCE_MAX               50

#define DMG_DANGER_MIN              10
#define DMG_DANGER_MAX              50

//******************************************************************************
// DECISION MAKER DEFINES.
// Prefix: DM.
//******************************************************************************

#define DM_ATR_CONST                9
#define DM_ACT_CONST                9
#define DM_PATH_TO_HUM_MATRIX       "res/humanoid_decision_matrix.txt"
#define DM_PATH_TO_NHUM_MATRIX      "res/non_humanoid_decision_matrix.txt"

//******************************************************************************
// CREATURE DEFINES.
// Prefix: CREAT.
//******************************************************************************

// Values of these coeffiecients should lay in range [CREAT_*_MIN, CREAT_*_MAX].

/// Minimum possible value of max_health.
#define CREAT_HEALTH_MIN            50
/// Maximum possible value of max_health.
#define CREAT_HEALTH_MAX            100

/// Minimum possible value of max_health.
#define CREAT_ENDURANCE_MIN         50
/// Maximum possible value of max_health.
#define CREAT_ENDURANCE_MAX         100

/// Minimum possible value of max_hunger.
#define CREAT_HUNGER_MIN            50
/// Maximum possible value of max_hunger
#define CREAT_HUNGER_MAX            100

/// Minimum possible value of max_sleepiness.
#define CREAT_SLEEPINESS_MIN        50
/// Maximum possible value of max_sleepiness.
#define CREAT_SLEEPINESS_MAX        100

/// Minimum possible value of force.
#define CREAT_FORCE_MIN             0
/// Maximum possible value of force.
#define CREAT_FORCE_MAX             100

/// Amount of steps to update basic attrs for creature.
#define CREAT_STEPS                 15 * TM_TICKS_PER_SECOND
/// Amount of steps to update danger.
#define CREAT_DANGER_STEPS          TM_TICKS_PER_SECOND / 2
/// Amount of steps to update health.
#define CREAT_REGEN_HEALTH_STEPS    30 * TM_TICKS_PER_SECOND
/// Amount if steps to update endurance.
#define CREAT_REGEN_ENDURANCE_STEPS 5  * TM_TICKS_PER_SECOND
/// Amount of steps to update need_in_descendants.
#define CREAT_DESC_STEPS            150 * TM_TICKS_PER_SECOND
/// Amount of steps to update age.
#define CREAT_AGE_STEPS             500 * TM_TICKS_PER_SECOND

/// Amount of health regeneration steps while sleeping
#define CREAT_SLEEP_REGEN_HEALTH    9
/// Amount of endurance regeneration steps while sleeping
#define CREAT_SLEEP_REGEN_ENDURANCE 4

/// Amount of health regeneration steps while relaxing
#define CREAT_RELAX_REGEN_HEALTH    2
/// Amount of endurance regeneration steps while sleeping
#define CREAT_RELAX_REGEN_ENDURANCE 2

/// Changes of hunger for one step
#define CREAT_DELTA_HUNGER          2
/// Changes of sleepiness for one step
#define CREAT_DELTA_SLEEP           1

/// Changes of health
#define CREAT_DELTA_HEALTH          1

/// Changes of endurance
#define CREAT_DELTA_ENDUR           1

/// Starving steps.
#define CREAT_STARVING_STEPS        (TM_TICKS_PER_SECOND / 2)

/// When delta is more than this const, creature makes new decision
#define CREAT_CRIT_CONST            40

/// Constant for evaluating danger for creatures.
#define CREAT_DANGER_FACTOR             5

/// Constant for evaluating distance at which immovable objects are dangerous
#define CREAT_DANGER_IMMOVABLE_FACTOR   20

/// Distance at which creatures rush at enemies.
#define CREAT_RUSH_DISTANCE             4

//******************************************************************************
// CREATURES ATTRIBUTES DEFINES.
// Prefix: ATTR.
//******************************************************************************

/// Attribute hunger
#define ATTR_HUNGER                 0
/// Attribute sleepiness
#define ATTR_SLEEPINESS             1
/// Attribute need_in_house
#define ATTR_NEED_IN_HOUSE          2
/// Attribute need in points
#define ATTR_NEED_IN_POINTS         3
/// Attribute laziness
#define ATTR_LAZINESS               4
/// Attribute health
#define ATTR_HEALTH                 5
/// Attribute communication
#define ATTR_COMMUNICATION          6
/// Attribute safety
#define ATTR_DANGER                 7
/// Attribute need in descendant
#define ATTR_NEED_IN_DESC           8

//******************************************************************************
// HUMANOID'S DEFINES.
// Prefix: HUM.
//******************************************************************************

// Values of these coeffiecients should lay in range [HUM_*_MIN, HUM_*_MAX].

/// Minimum possible value of humanoid's max_age.
#define HUM_AGE_MIN                 40
/// Maximum possible value of humanoid's max_age.
#define HUM_AGE_MAX                 50

/// Minimum possible value of humanoid's max_sociability.
#define HUM_SOCIABILITY_MIN         0
/// Maximum possible value of humanoid's max_sociability.
#define HUM_SOCIABILITY_MAX         100

/// Minimum possible value of humanoid's diligence.
#define HUM_LAZINESS_MIN            0
/// Maximum possible value of humanoid's diligence.
#define HUM_LAZINESS_MAX            100

/// Minimum possible value of humanoid's bravery
#define HUM_BRAVERY_MIN             0
/// Maximum possible value of humanoid's bravery
#define HUM_BRAVERY_MAX             100

/// Changes of need in descendant for one step
#define HUM_DELTA_NEED_IN_DESC      1
/// Changes of sociability for one step
#define HUM_DELTA_SOC               1
/// Amount of steps to decrease sleepiness
#define HUM_DECR_SLEEP_STEPS        150
/// Amount of steps to decrease sleepiness
#define HUM_DECR_ENDUR_STEPS        100

/// Space in inventory which is necessary in cratical situation
#define HUM_CRIT_SPACE              2

//******************************************************************************
// NONHUMANOID'S DEFINES.
// Prefix: NHUM.
//******************************************************************************

// Values of these coeffiecients should lay in range [NHUM_*_MIN, NHUM_*_MAX].

/// Minimum possible value of non-humanoid's max_age.
#define NHUM_AGE_MIN                10
/// Maximum possible value of non-humanoid's max_age.
#define NHUM_AGE_MAX                20

/// Changes of need_in_descendant for one step.
#define NHUM_DELTA_NEED_IN_DESC     2

/// Amount of steps to decrease sleepiness.
#define NHUM_DECR_SLEEP_STEPS       100

/// Amount of steps to change non-humanoid's roaming direction.
#define NHUM_ROAM_STEPS             300

//******************************************************************************
// REGENERATION'S DEFINES.
// Prefix: REG.
//******************************************************************************

/// Delta health of building "per" one res.
#define REG_BUILDING_COEF           10

/// Delta health for resource.
#define REG_RES_COEF                10

#endif // BASIC_DEFINES_H

