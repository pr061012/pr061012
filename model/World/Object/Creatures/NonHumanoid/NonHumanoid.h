/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef NON_HUMANOID_H
#define NON_HUMANOID_H

#include "../Creature.h"

/**
 * @class NonHumanoid
 * @brief NonHumanoid is silly creature, has only few goals in its life: food
 *        and sleep.
 */
class NonHumanoid : public Creature
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Random constructor (creates NonHumanoid with really random
     *        attributes).
     * @param dmaker    non-humanoid's decision maker
     */
    NonHumanoid(const DecisionMaker & dmaker);

    /**
     * @brief Destructor
     */
    ~NonHumanoid();

    //**************************************************************************
    // NON_HUMANOID ACTIONS.
    //**************************************************************************

    /**
     * @brief  Gets actions.
     * @return vector with actions.
     */
    std::vector <Action> * getActions();

    //**************************************************************************
    // NON-HUMANOID'S LOGICS.
    //**************************************************************************
private:
    void updateAge();
    void updateCommonAttrs();
    void updateNeedInDesc();
    void updateSafety();
    /// The direction of humanoid
    float angle;

    /// Amount of steps before decreasion of sleepiness. When NHUM is sleeping
    unsigned int decr_sleep_step;

    /// Current decision of non_hum
    CreatureAction current_decision;
};

#endif // NON_HUMANOID_H
