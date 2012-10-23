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
    Weather();

    /**
     * @brief Destructor.
     */
    ~Weather();

    //**************************************************************************
    // STEP.
    //**************************************************************************

	/**
     * @brief Does something with objects in window.
	 */
    void step();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

	/**
     * @brief Set the value of subtype.
     * @param new_var   the new value of subtype
     */
    void setSubtype(WeatherType new_var);

	/**
     * @brief  Get the value of subtype.
	 * @return the value of subtype
	 */
    WeatherType getSubtype();

	/**
     * @brief Set the value of window.
     * @param new_var   the new value of window
	 */
    void setWindow(ObjectHeap * new_var);

	/**
     * @brief  Get the value of window.
	 * @return the value of window
	 */
    ObjectHeap* getWindow();

	/**
     * @brief Set the value of view_area.
     * @param new_var   the new value of view_area
	 */
    void setViewArea(Frame new_var);

	/**
     * @brief  Get the value of view_area
	 * @return the value of view_area
	 */
    Frame getViewArea();

private:
    /// Weather type.
    WeatherType subtype;

    /// Pointer to the window in Indexator. Initializes in constructor.
    ObjectHeap * window;

    /// Effect area. Needed for Indexator for window's contents finding.
    Frame view_area;
};

#endif // WEATHER_H
