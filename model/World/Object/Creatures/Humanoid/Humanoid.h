/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef HUMANOID_H
#define HUMANOID_H

#include <string>

#include "../Creature.h"

/**
 * @class Humanoid
 * @brief Humanoid is clever creature, has own ideals, thoughts and preferences.
 *        Humanoids are base element in game, they makes their own decisions
 *        and influence and change world around them.
 */
class Humanoid : virtual public Creature
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Random constructor (creates Humanoid with really random
     *        attributes).
     * @param dmaker    humanoid's decision maker
     */
    Humanoid(const DecisionMaker & dmaker);

    /**
     * @brief Destructor
     */
    ~Humanoid();

    //**************************************************************************
    // HUMANOID'S LOGICS.
    //**************************************************************************

    /**
     * @brief Makes a next step.
     */
    void step();

private:
    //**************************************************************************
    // COMMON INFORMATION.
    //**************************************************************************

    /// Humanoid's name.
    std::string name;

    //**************************************************************************
    // RELATIVE COEFFICIENTS.
    // May have any value. In decision maker we use only quotient of them.
    // One coefficient is declared in Object class -- health and max_health.
    //**************************************************************************

    /// Current value of satiety.
    unsigned int satiety;
    /// Maximum possible value of satiety.
    unsigned int max_satiety;

    /// Current value of sleepiness.
    unsigned int sleepiness;
    /// Maximum possible value of sleepiness.
    unsigned int max_sleepiness;

    /// Current sociability.
    unsigned int sociability;
    /// Maximum possible value of sociability.
    unsigned int max_sociability;

    //**************************************************************************
    // ABSOLUTE COEFFICIENTS.
    // May take only value in range [0, 100].
    //**************************************************************************

    /// Current safety.
    unsigned int safety;

    /// Diligence (const during time).
    unsigned int diligence;

    /// Contentment by house.
    unsigned int cont_by_house;

    /// Resource availability.
    unsigned int res_availability;
};

#endif // HUMANOID_H
