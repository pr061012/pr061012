/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef CREATURE_H
#define CREATURE_H

#include "../Object.h"
#include "../../DecisionMaker/DecisionMaker.h"
#include "../../ObjectHeap/ObjectHeap.h"
#include "../../../BasicTypes.h"

/**
 * @class Creature
 * @brief Abstract Creature class.
 */


class Creature : public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Random constructor (creates Creature with really random
     *        attributes).
     * @param type      creature's type
     * @param dmaker    creature's decision maker
     */
    Creature(CreatureType type, const DecisionMaker & dmaker);

    /**
     * @brief Destructor.
     */
    ~Creature();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Set the value of creature's window.
     * @param window    the new value of window
     */
    void setWindow(const ObjectHeap * window);

    /**
     * @brief  Get the value of creature's window.
     * @return the window
     */
    const ObjectHeap * getWindow();

    /**
     * @brief Set the value of view_area.
     * @param view_area the new value of view_area
     */
    void setViewArea(Shape view_area);

    /**
     * @brief  Get the value of view_area.
     * @return the value of view_area
     */
    Shape getViewArea();

    /**
     * @brief Set the value of age.
     * @param age   new value of age
     */
    void setAge(unsigned int age);

    /**
     * @brief  Get the value of age.
     * @return the value of age
     */
    unsigned int getAge();

    /**
     * @brief Set the value of max age.
     * @param age   new value of max age
     */
    void setMaxAge(unsigned int max_age);

    /**
     * @brief  Get the value of max age.
     * @return the value of max age
     */
    unsigned int getMaxAge();

    /**
     * @brief Set the value of health.
     * @param health   new value of health
     */
    void setHealth(unsigned int health);

    /**
     * @brief  Get the value of health.
     * @return the value of health
     */
    unsigned int getHealth();

    /**
     * @brief Set the value of max health.
     * @param health   new value of max health
     */
    void setMaxHealth(unsigned int max_health);

    /**
     * @brief  Get the value of max age.
     * @return the value of max age
     */
    unsigned int getMaxHealth();

    //**************************************************************************
    // OBJECT'S LIFE.
    //**************************************************************************

    /**
     * @brief Decreases object's health.
     * @param delta health to decrease
     */
    void decreaseHealth(unsigned int delta);

    /**
     * @brief Increases object's health.
     * @param delta health to increase
     */
    void increaseHealth(unsigned int delta);

private:
    /**
     * @brief Matrix of attributes
     */
    arma::mat attrs;

    /// Creature's type.
    const CreatureType subtype;

    /// Reference to creature's DecisionMaker.
    const DecisionMaker & brains;

    /// Creature's window with visible objects.
    const ObjectHeap * window;

    /// Creature's inventory.
    ObjectHeap * inventory;

    /// View area for Indexator.
    Shape view_area;

    /// Current creature's action.
    CreatureAction current_action;

    /// Current age.
    unsigned int age;

    /// Maximum possible age.
    unsigned int max_age;

    /// Current health.
    unsigned int health;

    /// Maximum possible health.
    unsigned int max_health;

	// Quotient = 100 => creature wants sleep.

    /// Current value of sleepiness.
    unsigned int sleepiness;
    /// Maximum possible value of sleepiness.
    unsigned int max_sleepiness;

	///Current value of need_in_descendants (0-100)
	unsigned int need_in_descendants;

	// If = 100, creature is in danger.
    /// Current safety.
    unsigned int safety;

	// Quotient = 100 => creature wants eat.
    /// Current value of hunger.
    unsigned int hunger;
    /// Maximum possible value of hunger.
    unsigned int max_hunger;



#endif // CREATURE_H
