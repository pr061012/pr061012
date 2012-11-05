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
class NonHumanoid : virtual public Creature
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
    /**
     * @brief Updates hunger, sleepiness, health
     */
    void updateCommonAttrs();

    //Steps for updates
    unsigned int common_steps;
    unsigned int age_steps;
    unsigned int desc_steps;
    unsigned int safety_steps;

    /**
     * @brief Updates age
     */
    void updateAge();

    /**
     * @brief Updates need_in_descendants
     */
    void updateNeedInDesc();

    /**
     * @brief Updates safety
     */
    void updateSafety();

    /**
     * @brief Updates common attrs
     */
    void updateCommonAttrs();

};

#endif // NON_HUMANOID_H
