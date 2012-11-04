/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef DEFINES_H
#define DEFINES_H
//******************************************************************************
// COMMON DEFINES.
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

//******************************************************************************
// NONHUMANOID'S DEFINES.
// Prefix: NHUM.
//******************************************************************************

// Values of these coeffiecients should lay in range [NHUM_*_MIN, NHUM_*_MAX].

/// Minimum possible value of non-humanoid's max_age.
#define NHUM_AGE_MIN        10
/// Maximum possible value of non-humanoid's max_age.
#define NHUM_AGE_MAX        20

#endif // DEFINES_H
