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
class Humanoid : public Creature
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
    virtual ~Humanoid();

    //**************************************************************************
    // HUMANOID'S ACTIONS
    //**************************************************************************

    /**
    * @brief  Gets actions.
    * @return vector with actions.
    */
    std::vector <Action>* getActions();

private:
    //**************************************************************************
    // IDS.
    //**************************************************************************

    static int CURRENT_ID;

    const unsigned int id;

    //**************************************************************************
    // COMMON INFORMATION.
    //**************************************************************************

    /// Humanoid's name.
    std::string name;

    //**************************************************************************
    // RELATIVE COEFFICIENTS.
    // May have any value. In decision maker we use only quotient of them (in
    // percents).
    // Some coefficients are declared in Object class -- health and max_health,
	// sleepiness and max_sleepiness, hunger and max_hunger.
    //**************************************************************************

    // Quotient = 100 => humanoid wants to talk with somebody.
    /// Current sociability.
    unsigned int sociability;
    /// Maximum possible value of sociability.
    unsigned int max_sociability;

    //**************************************************************************
    // ABSOLUTE COEFFICIENTS.
    // May take only value in range [0, 100].
    //**************************************************************************

    // If = 100, humanoid is very lazy.
    /// Laziness (const during time).
    unsigned int laziness;  //const?

    // If = 100, humanoid needs new house.
    /// Need in house.
    unsigned int need_in_house;

    // If = 100, humanoid needs resources.
    /// Need in points.
    unsigned int need_in_points;
private:
    void updateAge();
    void updateCommonAttrs();
    void updateNeedInDesc();
    void updateSafety();

    //**************************************************************************
    // HUMANOID'S LOGICS.
    //**************************************************************************
    /// Detailed action of humanoid
    DetailedHumAction detailed_act;

    /**
     * @brief Humanoid chooses the next action
     * @return CratureAction action
     */
    DetailedHumAction chooseAction(CreatureAction action); // is it good name?

    /**
     * @brief Humanoid chooses the way to decrease his hunger
     * @return DetailedHumAction detailed_act
     */
    DetailedHumAction chooseWayToEat();

    /**
     * @brief Humanoid chooses the way to decrease his sleepiness
     * @return DetailedHumAction detailed_act
     */
    DetailedHumAction chooseWayToSleep();

    /**
     * @brief Humanoid chooses the way to build his house
     * @return DetailedHumAction detailed_act
     */
    DetailedHumAction chooseWayToBuild();

    /**
     * @brief Humanoid chooses the way to escape danger
     * @return DetailedHumAction detailed_act
     */
    DetailedHumAction chooseWayToEscape();

    /**
     * @brief Humanoid chooses the way to relax
     * @return DetailedHumAction detailed_act
     */
    DetailedHumAction chooseWayToRelax();
};

#endif // HUMANOID_H
