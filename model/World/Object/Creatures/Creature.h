/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef CREATURE_H
#define CREATURE_H

#include "../Object.h"
#include "../../DecisionMaker/DecisionMaker.h"
#include "../../ObjectHeap/ObjectHeap.h"
#include "../../../../common/BasicTypes.h"

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
     * @brief Get subtype
     * @return creature subtype
     */
    CreatureType getSubtype();

    /**
     * @brief Set the value of creature's window.
     * @param window    the new value of window
     */
    void setObjectsAround(ObjectHeap objects_around);

    /**
     * @brief  Get the value of creature's window.
     * @return the window
     */
    ObjectHeap* getObjectsAround();

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
    void setAge(uint age);

    /**
     * @brief  Get the value of age.
     * @return the value of age
     */
    uint getAge();

    /**
     * @brief Set the value of max age.
     * @param max_age   new value of max age
     */
    void setMaxAge(uint max_age);

    /**
     * @brief  Get the value of max age.
     * @return the value of max age
     */
    uint getMaxAge();

    /**
     * @brief Set the value of health.
     * @param health   new value of health
     */
    void setHealth(uint health);

    /**
     * @brief  Get the value of health.
     * @return the value of health
     */
    uint getHealth();

    /**
     * @brief Set the value of max health.
     * @param max_health   new value of max health
     */
    void setMaxHealth(uint max_health);

    /**
     * @brief  Get the value of max age.
     * @return the value of max age
     */
    uint getMaxHealth();

    /**
     * @brief  Get inventory
     * @return inventory
     */
    ObjectHeap * getInventory();

    //**************************************************************************
    // CHANGING HEALTH.
    //**************************************************************************

    /**
     * @brief Decreases object's health.
     * @param delta health to decrease
     */
    void decreaseHealth(uint delta);

    /**
     * @brief Increases object's health.
     * @param delta health to increase
     */
    void increaseHealth(uint delta);

    //**************************************************************************
    // Increase attributes
    //**************************************************************************
    /**
     * @brief Increases satiety level
     */
    void feed(uint delta);

    //**************************************************************************
    // INHERETED THINGS.
    //**************************************************************************

    uint getHealthPoints() const;
    uint getMaxHealthPoints() const;
    void damage(uint delta);
    void heal(uint delta);

private:
    /// Creature's type.
    const CreatureType subtype;


    /// View area for Indexator.
    Shape view_area;

protected:
    /// Creature's inventory.
    ObjectHeap * inventory;

    /**
     * @brief    Calculate the angle between first (this) and second (aim) object
     * @return   angle
     */
    double setDirection();

    /// Force of creations
    uint force;

    /// Endurance of creations
    uint endurance;

    /// Current creature's action.
    CreatureAction current_action;

    /// Creature's enviroment
    ObjectHeap objects_around;

     /// Matrix of attributes
    arma::mat attrs;

    /// Reference to creature's DecisionMaker.
    const DecisionMaker & brains;

    /// Current age.
    uint age;

    /// Maximum possible age.
    uint max_age;

    /// Current health.
    uint health;

    /// Maximum possible health.
    uint max_health;

    // Quotient = 100 => creature wants sleep.

    /// Current value of sleepiness.
    uint sleepiness;
    /// Maximum possible value of sleepiness.
    uint max_sleepiness;

    /// Current value of need_in_descendants (0-100)
	uint need_in_descendants;

    // If = 100, creature is in danger.
    /// Current safety.
    uint safety;

    // Quotient = 100 => creature wants eat.
    /// Current value of hunger.
    uint hunger;
    /// Maximum possible value of hunger.
    uint max_hunger;

    /// Amount for steps to common update.
    uint common_steps;
    /// Amount for steps to age update.
    uint age_steps;
    /// Amount for steps to need_in_descendant update.
    uint desc_steps;
    /// Amount for steps to safety update.
    uint safety_steps;

    //**************************************************************************
    // DIRECTIONS
    //**************************************************************************
    /// The direction of creature
    double angle;
    /// Current direction (subject) oh NHum
    Object* aim;

    //**************************************************************************
    // DECISION
    //**************************************************************************
    /// Current decision of creature
    CreatureAction current_decision;

    //**************************************************************************
    // UPDATES
    //**************************************************************************
    /**
     * @brief Updates age
     */
    virtual void updateAge() = 0;

    /**
     * @brief Updates need_in_descendants
     */
    virtual void updateNeedInDesc() = 0;

    /**
     * @brief Updates safety
     */
    void updateSafety();

    /**
     * @brief Updates hunger, sleepiness, health
     */
    virtual void updateCommonAttrs() = 0;

    //**************************************************************************
    // CHOOSE THE DIRECTION
    //**************************************************************************
    void chooseDirectionToEscape();
};


#endif // CREATURE_H
