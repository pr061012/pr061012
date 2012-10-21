/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef CREATURE_H
#define CREATURE_H

#include "../Object.h"
#include "../../DecisionMaker/DecisionMaker.h"
#include "../../ObjectHeap/ObjectHeap.h"

/**
  * @class Creature
  * @brief Abstract Creature class.
  */

class Creature : virtual public Object
{
public:
	/**
     * @brief Random constructor (creates Creature with really random
     *        attributes).
     * @param brains    creature's decision maker
	 */
    Creature(const DecisionMaker & brains);

	/**
     * @brief Destructor.
	 */
    ~Creature();

    /**
     * @brief Make a next step.
     */
    virtual void step() = 0;

    /**
     * @brief Set the value of creature's window.
     * @param window    the new value of window
     */
    void setWindow(const ObjectHeap * window);

    /**
     * @brief Get the value of creature's window.
     * @return the window
     */
    const ObjectHeap * getWindow();

    /**
     * @brief Set the value of view_area.
     * @param view_area the new value of view_area
     */
    void setViewArea(Frame view_area);

    /**
     * @brief Get the value of view_area.
     * @return the value of view_area
     */
    Frame getViewArea();

private:
    /// Link to creature's DecisionMaker.
    const DecisionMaker & brains;

    /// Creature's window with visible objects.
    const ObjectHeap * window;

    /// Creature's inventory.
	ObjectHeap * inventory;

    /// View area for Indexator.
    Frame view_area;
};

#endif // CREATURE_H
