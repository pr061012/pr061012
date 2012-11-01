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
    // IDS.
    //**************************************************************************

    static int CURRENT_ID;

    const unsigned int id;

    //**************************************************************************
    // COMMON INFORMATION.
    //**************************************************************************

    /// Current humanoid's action.
    ActionType action;

    /// Humanoid's name.
    std::string name;

    //**************************************************************************
    // RELATIVE COEFFICIENTS.
    // May have any value. In decision maker we use only quotient of them (in
    // percents).
    // One coefficient is declared in Object class -- health and max_health.
    //**************************************************************************

    // Quotient = 100 => humanoid wants eat.
    /// Current value of hunger.
    unsigned int hunger;
    /// Maximum possible value of hunger.
    unsigned int max_hunger;

    // Quotient = 100 => humanoid wants sleep.
    /// Current value of sleepiness.
    unsigned int sleepiness;
    /// Maximum possible value of sleepiness.
    unsigned int max_sleepiness;

    // Quotient = 100 => humanoid wants to talk with somebody.
    /// Current sociability.
    unsigned int sociability;
    /// Maximum possible value of sociability.
    unsigned int max_sociability;

    //**************************************************************************
    // ABSOLUTE COEFFICIENTS.
    // May take only value in range [0, 100].
    //**************************************************************************

    // If = 100, humanoid is in danger.
    /// Current safety.
    unsigned int safety;

    // If = 100, humanoid is very lazy.
    /// Laziness (const during time).
    unsigned int laziness;

    // If = 100, humanoid needs new house.
    /// Need in house.
    unsigned int need_in_house;

    // If = 100, humanoid needs resources.
    /// Need in resources.
    unsigned int need_in_res;
};

#endif // HUMANOID_H
