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

    //******************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //******************************************************************************

    Weather();

    ~Weather();

	/**
	 * Что-то делает с объектами в window.
	 */
    void step();

	/**
	 * Set the value of subtype
	 * @param new_var the new value of subtype
	 */

    //******************************************************************************
    // ACCESSORS.
    //******************************************************************************

    void setSubtype(WeatherType new_var);

	/**
	 * Get the value of subtype
	 * @return the value of subtype
	 */
    WeatherType getSubtype();
	/**
	 * Set the value of window
	 * Указатель на окно в индексаторе. Задаётся при инициализации.
	 * @param new_var the new value of window
	 */
    void setWindow(ObjectHeap * new_var);

	/**
	 * Get the value of window
	 * Указатель на окно в индексаторе. Задаётся при инициализации.
	 * @return the value of window
	 */
    ObjectHeap* getWindow();

	/**
	 * Set the value of view_area
	 * Область воздействия. Нужен для Indexator для определения содержимого window.
	 * @param new_var the new value of view_area
	 */
    void setViewArea(Frame new_var);

	/**
	 * Get the value of view_area
	 * Область воздействия. Нужен для Indexator для определения содержимого window.
	 * @return the value of view_area
	 */
    Frame getViewArea();

private:

    WeatherType subtype;
    /// Указатель на окно в индексаторе. Задаётся при инициализации.
    ObjectHeap * window;
    /// Область воздействия. Нужен для Indexator для определения содержимого window.
    Frame view_area;
};

#endif // WEATHER_H
