/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECT_H
#define OBJECT_H

#include "../../Utilities/Frame/Frame.h"
#include "../../Utilities/VisualState/VisualState.h"
#include "../../BasicTypes.h"

/**
 * @class Object
 * @brief Abstract Object class
 */


class Object
{
private:

    /// Type of object
    int type;

    /// Сoordinatesобъекта.
    Frame frame;

    /// Отображение объекта для графики.
    VisualState visual_state;

    ///
    bool destroyed;

    /**
     * @brief Существа/здания - здоровье.
     * Погода - время жизни.
     * Ресурс - кол-во ресурса.
     * Инструмент - прочность.
    */

    /// Health of object
    int health;

    /// Бессмертие.
    bool immortal;
    int max_health;
    /// Угол поворота.
    double angle;

public:

    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     */
    Object();

	/**
     * @brief Destructor
	 */
    ~Object();

	/**
     * @brief Destroy object
	 */
    void destroy();


	/**
     * @brief
     * @param harm
	 */
    void damage(int harm);

    void initAttributes();
public:

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************


	/**
	 * Set the value of type
	 * @param new_var the new value of type
	 */

    void setType(int new_var);

	/**
	 * Get the value of type
	 * @return the value of type
	 */
    int getType();

	/**
     * @brief Set the value of frame
	 * Координаты и область объекта.
	 * @param new_var the new value of frame
	 */
    void setFrame(Frame new_var);

	/**
     * @brief Get the value of frame
	 * Координаты и область объекта.
	 * @return the value of frame
	 */

    Frame getFrame();

	/**
	 * Set the value of visual_state
	 * Отображение объекта для графики.
	 * @param new_var the new value of visual_state
	 */
    void setVisualState(VisualState new_var);

	/**
	 * Get the value of visual_state
	 * Отображение объекта для графики.
	 * @return the value of visual_state
	 */

    VisualState getVisualState();

	/**
	 * Set the value of destroyed
	 * @param new_var the new value of destroyed
	 */
    void setDestroyed(bool new_var);

	/**
	 * Get the value of destroyed
	 * @return the value of destroyed
	 */
    bool getDestroyed();


	/**
	 * Set the value of health
	 * Существа/здания - здоровье.
	 * Погода - время жизни.
	 * Ресурс - кол-во ресурса.
	 * Инструмент - прочность.
	 * @param new_var the new value of health
	 */
    void setHealth(int new_var);

	/**
	 * Get the value of health
	 * Существа/здания - здоровье.
	 * Погода - время жизни.
	 * Ресурс - кол-во ресурса.
	 * Инструмент - прочность.
	 * @return the value of health
	 */
    int getHealth();

	/**
	 * Set the value of immortal
	 * Бессмертие.
	 * @param new_var the new value of immortal
	 */
    void setImmortal(bool new_var);

	/**
	 * Get the value of immortal
	 * Бессмертие.
	 * @return the value of immortal
	 */
    bool getImmortal();

	/**
	 * Set the value of max_health
	 * @param new_var the new value of max_health
	 */
    void setMaxHealth(int new_var);

	/**
	 * Get the value of max_health
	 * @return the value of max_health
	 */
    int getMaxHealth();

	/**
	 * Set the value of angle
	 * Угол поворота.
	 * @param new_var the new value of angle
	 */
    void setAngle(double new_var);

	/**
	 * Get the value of angle
	 * Угол поворота.
	 * @return the value of angle
	 */
    double getAngle();

};

#endif // OBJECT_H
