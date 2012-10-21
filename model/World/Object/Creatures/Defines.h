/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef DEFINES_H
#define DEFINES_H

//******************************************************************************
// HUMANOID'S DEFINES.
// Prefix: HUM.
//******************************************************************************

// Values of these coeffiecients should lay in range [HUM_*_MIN, HUM_*_MAX].

/// Minimum possible value of humanoid's max_health.
#define HUM_HEALTH_MIN      50
/// Maximum possible value of humanoid's max_health.
#define HUM_HEALTH_MAX      100

/// Minimum possible value of humanoid's max_age.
#define HUM_MIN_AGE         40
/// Maximum possible value of humanoid's max_age.
#define HUM_MAX_AGE         50

/// Minimum possible value of humanoid's max_satiety.
#define HUM_MIN_SATIETY     50
/// Maximum possible value of humanoid's max_satiety.
#define HUM_MAX_SATIETY     100

/// Minimum possible value of humanoid's max_sleepiness.
#define HUM_MIN_SLEEPINESS  50
/// Maximum possible value of humanoid's max_sleepiness.
#define HUM_MAX_SLEEPINESS  100

/// Minimum possible value of humanoid's max_sociability.
#define HUM_MIN_SOCIABILITY 50
/// Maximum possible value of humanoid's max_sociability.
#define HUM_MAX_SOCIABILITY 100

/// Minimum possible value of humanoid's diligence.
#define HUM_MIN_DILIGENCE   50
/// Maximum possible value of humanoid's diligence.
#define HUM_MAX_DILIGENCE   100

//******************************************************************************
// NONHUMANOID'S DEFINES.
// Prefix: NHUM.
//******************************************************************************

// Values of these coeffiecients should lay in range [NHUM_*_MIN, NHUM_*_MAX].

/// Minimum possible value of non-humanoid's max_health.
#define NHUM_HEALTH_MIN     50
/// Maximum possible value of non-humanoid's max_health.
#define NHUM_HEALTH_MAX     100

/// Minimum possible value of non-humanoid's max_age.
#define NHUM_MIN_AGE        10
/// Maximum possible value of non-humanoid's max_age.
#define NHUM_MAX_AGE        20

#endif // DEFINES_H
