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
    // INHERETED THINGS.
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
     * @brief Set the value of window.
     * @param new_var   the new value of window
	 */
    void setWindow(ObjectHeap* new_var);

	/**
     * @brief  Get the value of window.
	 * @return the value of window
	 */
    ObjectHeap * getWindow();

private:
    /// Weather type.
    const WeatherType subtype;

    /// Covered objects. Is setted up by Controller using Weather shape.
    ObjectHeap * covered_objs;
};

#endif // WEATHER_H
