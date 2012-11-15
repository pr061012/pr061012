/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef NON_HUMANOID_H
#define NON_HUMANOID_H

#include "../Creature.h"
#include "../../../../BasicTypes.h"

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
    virtual ~NonHumanoid();

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
    //**************************************************************************
    // UPDATES
    //**************************************************************************
    void updateAge();
    void updateCommonAttrs();
    void updateNeedInDesc();
    void updateSafety();
    //**************************************************************************
    // AUXILIARY FUNTIONS
    //**************************************************************************

    /**
     * @brief    Find grass around NHum
     * @return   the nearest grass
     */
    void findGrass();

    /**
     * @brief    Calculate the angle between first (this) and second (aim) object
     * @return   angle
     */
    double setDirection();

    //**************************************************************************
    // Increase attributes
    //**************************************************************************
    /**
     * @brief    Increases satiety level
     */
    void feed();

    //**************************************************************************
    // DIRECTIONS
    //**************************************************************************
    /// The direction of non_humanoid
    double angle;
    /// Current direction (subject) oh NHum
    Object* aim;
    //**************************************************************************
    // UPDATE STEP
    //**************************************************************************
    /// Amount of steps before decreasion of sleepiness. When NHUM is sleeping
    unsigned int decr_sleep_step;

    //**************************************************************************
    // DECISION
    //**************************************************************************
    /// Current decision of non_hum
    CreatureAction current_decision;
    //**************************************************************************
    // TYPE
    //**************************************************************************
    NonHumanoidType type;
};

#endif // NON_HUMANOID_H
