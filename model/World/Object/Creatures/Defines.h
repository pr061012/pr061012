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

// Humanoids maximum health should lay in range [HUM_HEALTH_MIN,
// HUM_HEALTH_MAX].

/// Minimum possible value of humanoid's max_health.
#define HUM_HEALTH_MIN      50

/// Maximum possible value of humanoid's max_health.
#define HUM_HEALTH_MAX      100

/// Minimum possible value of humanoid's max_age.
#define HUM_MIN_AGE         40

/// Maximum possible value of humanoid's max_age.
#define HUM_MAX_AGE         50

//******************************************************************************
// NONHUMANOID'S DEFINES.
// Prefix: NHUM.
//******************************************************************************

// NonHumanoids maximum health should lay in range [NHUM_HEALTH_MIN,
// NHUM_HEALTH_MAX].

/// Minimum possible value of non-humanoid's max_health.
#define NHUM_HEALTH_MIN     50

/// Maximum possible value of non-humanoid's max_health.
#define NHUM_HEALTH_MAX     100

/// Minimum possible value of non-humanoid's max_age.
#define NHUM_MIN_AGE        10

/// Maximum possible value of non-humanoid's max_age.
#define NHUM_MAX_AGE        20

#endif // DEFINES_H
