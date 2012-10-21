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
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    Object();

    /**
     * @brief Destructor.
     */
    ~Object();

    /**
     * @brief Destroy object.
     */
    void destroy();

    /**
     * @brief Damages object.
     * @param harm  about of damage
     */
    void damage(unsigned int harm);

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

	/**
     * @brief Set the value of type.
     * @param new_var   the new value of type
	 */
    void setType(int new_var);

	/**
     * @brief Get the value of type.
	 * @return the value of type
	 */
    int getType();

	/**
     * @brief Set the value of frame.
     * @param new_var   the new value of frame
	 */
    void setFrame(Frame new_var);

	/**
     * @brief Get the value of frame.
	 * @return the value of frame
	 */
    Frame getFrame();

	/**
     * @brief Set the value of visual_state.
     * @param new_var   the new value of visual_state
	 */
    void setVisualState(VisualState new_var);

	/**
     * @brief Get the value of visual_state.
	 * @return the value of visual_state
	 */
    VisualState getVisualState();

	/**
     * @brief Set the value of destroyed.
     * @param new_var   the new value of destroyed
	 */
    void setDestroyed(bool new_var);

	/**
     * @brief Get the value of destroyed.
	 * @return the value of destroyed
	 */
    bool getDestroyed();

	/**
     * @brief Set the value of health.
	 * @param new_var the new value of health
	 */
    void setHealth(unsigned int new_var);

	/**
     * @brief Get the value of health.
	 */
    unsigned int getHealth();

	/**
     * @brief Set the value of immortal.
     * @param new_var   the new value of immortal
	 */
    void setImmortal(bool new_var);

	/**
     * @brief Get the value of immortal.
	 * @return the value of immortal
	 */
    bool getImmortal();

	/**
     * @brief Set the value of max_health.
     * @param new_var   the new value of max_health
	 */
    void setMaxHealth(unsigned int new_var);

	/**
     * @brief Get the value of max_health.
	 * @return the value of max_health
	 */
    unsigned int getMaxHealth();

	/**
     * @brief Set the value of angle.
     * @param new_var   the new value of angle
	 */
    void setAngle(double new_var);

	/**
     * @brief Get the value of angle.
	 * @return the value of angle
	 */
    double getAngle();
    
private:
    /// Object's type.
    ObjectType type;

    /// Object's coordinates and frame.
    Frame frame;

    /// Object's visual state (for View).
    VisualState visual_state;

    /// Is object destroyed or not.
    bool destroyed;

    /// @brief Object's health.
    ///        * buildings and creatures -- health
    ///        * weather -- living time
    ///        * resource -- amount of resource
    ///        * tool -- durability
    unsigned int health;

    /// Maximum amount of health.
    unsigned int max_health;

    /// Immortality.
    bool immortality;

    /// Angle of rotation.
    double angle;


};

#endif // OBJECT_H
