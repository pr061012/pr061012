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
class Creature : virtual public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Random constructor (creates Creature with really random
     *        attributes).
     * @param dmaker    creature's decision maker
     */
    Creature(const DecisionMaker & dmaker);

    /**
     * @brief Destructor.
     */
    ~Creature();

    //**************************************************************************
    // CREATURE'S LOGICS.
    //**************************************************************************

    /**
     * @brief Makes a next step.
     */
    virtual void step() = 0;

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
    void setViewArea(Frame view_area);

    /**
     * @brief  Get the value of view_area.
     * @return the value of view_area
     */
    Frame getViewArea();

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

private:
    /// Link to creature's DecisionMaker.
    const DecisionMaker & brains;

    /// Creature's window with visible objects.
    const ObjectHeap * window;

    /// Creature's inventory.
    ObjectHeap * inventory;

    /// View area for Indexator.
    Frame view_area;

    /// Current creature's action.
    ActionType current_action;

    /// Current age.
    unsigned int age;

    /// Maximum possible age.
    unsigned int max_age;
};

#endif // CREATURE_H
