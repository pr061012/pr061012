/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef WEATHER_H
#define WEATHER_H

#include "../Object.h"
#include "../../ObjectHeap/ObjectHeap.h"

/**
 * @class Weather
 * @brief Weather class
 */
class Weather : public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    Weather(WeatherType type, uint living_steps = 0);

    /**
     * @brief Destructor.
     */
    ~Weather();

    //**************************************************************************
    // WEATHER ACTIONS.
    //**************************************************************************

    /**
     * @brief  Gets actions.
     * @return vector with actions.
     */
    std::vector <Action> * getActions();

    //**************************************************************************
    // WEATHER TYPE.
    //**************************************************************************

	/**
     * @brief  Get the value of subtype.
	 * @return the value of subtype
	 */
    WeatherType getSubtype() const;

    //**************************************************************************
    // DAMAGE/HEAL.
    //**************************************************************************

    /**
     * @brief Damages weather (actually does nothing).
     * @param delta amount of damage
     */
    void damage(uint delta){}

    /**
     * @brief ''Heals'' weather (actually does nothing).
     * @param delta amount of healing points
     */
    void heal(uint delta){}

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

	/**
     * @brief  Gets reference to heap with covered objects. This heap can be
     *         modified (in fact, Controller modify it by using Weather shape).
     * @return reference to heap with covered objects
	 */
    ObjectHeap * getCoveredObjects();

    /**
     * @brief  Gets amount of living steps.
     * @return amount of living steps.
     */
    uint getLivingSteps() const;

private:
    /// Weather type.
    const WeatherType subtype;

    /// Covered objects. Is setted up by Controller by using Weather shape.
    ObjectHeap * covered_objs;

    /// Steps for living.
    uint steps;
};

#endif // WEATHER_H
