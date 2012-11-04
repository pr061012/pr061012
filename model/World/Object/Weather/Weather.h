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
class Weather : virtual public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    Weather(WeatherType type);

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
    WeatherType getSubtype();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

	/**
     * @brief  Get reference to heap with covered objects. This heap can be
     *         modified (in fact, Controller modify it by using Weather shape).
     * @return reference to heap with covered objects
	 */
    ObjectHeap * getCoveredObjects();

private:
    /// Weather type.
    const WeatherType subtype;

    /// Covered objects. Is setted up by Controller by using Weather shape.
    ObjectHeap * covered_objs;
};

#endif // WEATHER_H
