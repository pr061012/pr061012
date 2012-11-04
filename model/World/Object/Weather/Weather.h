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
    // ACCESSORS.
    //**************************************************************************

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
    ObjectHeap* getWindow();

	/**
     * @brief Set the value of view_area.
     * @param new_var   the new value of view_area
	 */
    void setViewArea(Shape new_var);

	/**
     * @brief  Get the value of view_area
	 * @return the value of view_area
	 */
    Shape getViewArea();

private:
    /// Weather type.
    const WeatherType subtype;

    /// Pointer to the window in Indexator. Initializes in constructor.
    ObjectHeap * window;

    /// Effect area. Needed for Indexator for window's contents finding.
    Shape view_area;
};

#endif // WEATHER_H
