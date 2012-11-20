/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef HUMANOID_H
#define HUMANOID_H

#include <string>

#include "../Creature.h"
#include "../../Building/Building.h"

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
    Humanoid(const DecisionMaker& dmaker);

    /**
     * @brief Destructor
     */
    virtual ~Humanoid();

    //**************************************************************************
    // HUMANOID'S ACTIONS
    //**************************************************************************

    std::vector <Action>* getActions();
    void receiveMessage(Message message);

private:
    //**************************************************************************
    // IDS.
    //**************************************************************************

    static int CURRENT_HUM_ID;

    const unsigned int hum_id;

    //**************************************************************************
    // COMMON INFORMATION.
    //**************************************************************************

    /// Humanoid's name.
    std::string name;
    //**************************************************************************
    // HUMANOID'S OBJECTS
    //**************************************************************************
    Building* home;
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
    /// Bravery
    uint bravery;

    //**************************************************************************
    // MEMORY
    //**************************************************************************
    ObjectHeap* visual_memory;
    /**
     * @brief Memorize seen object
     */
    void visualMemorize();

    //**************************************************************************
    // UPDATES
    //**************************************************************************
    void updateAge();
    void updateCommonAttrs();
    void updateNeedInDesc();

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

    //**************************************************************************
    // UPDATE STEP
    //**************************************************************************
    /// Amount of steps before decreasion of sleepiness. When HUM is sleeping
    uint decr_sleep_step;
    /// Amount of steps before decreasion of endurance. When HUM is escaping
    uint decr_endur_step;
};

#endif // HUMANOID_H
