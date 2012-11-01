/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "../../Utilities/Shape/Shape.h"
#include "../../BasicTypes.h"
#include "../PendingAction/PendingAction.h"

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
    Object(ObjectType type);

    /**
     * @brief Destructor.
     */
    ~Object();

    //**************************************************************************
    // OBJECT'S LIFE.
    //**************************************************************************

    /**
     * @brief Destroy object.
     */
    void destroy();

    /**
     * @brief Damages object.
     * @param harm  about of damage
     */
    void damage(unsigned int harm);

    /**
     * @brief Treat object
     * @param point point of treat
     */
    void treat(unsigned int point);

    /**
     * @brief  Gets objects pending actions.
     * @return vector with pending actions.
     */
    virtual std::vector <PendingAction *> getPendingActions() = 0;

    /**
     * @brief Receives message.
     * @param action    message
     */
    virtual void receiveMessage(PendingAction * action) = 0;

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Get the value of type.
     * @return the value of type
     */
    ObjectType getType();

    /**
     * @brief Set the value of shape.
     * @param new_var   the new value of shape
     */
    void setShape(Shape new_var);

    /**
     * @brief Get the value of shape.
     * @return the value of shape
     */
    Shape getShape();

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
     * @return the value of health
     */
    unsigned int getHealth();

    /**
     * @brief Set the value of immortality.
     * @param new_var   the new value of immortality
     */
    void setImmortality(bool new_var);

    /**
     * @brief Get the value of immortality.
     * @return the value of immortality
     */
    bool getImmortality();

    /**
     * @brief Set the value of max_health.
     * @param new_var the new value of max_health
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
    const ObjectType type;

    /// Object's coordinates and frame.
    Shape shape;

    /// Is object destroyed or not.
    bool destroyed;

    /** @brief Object's health.
     *        * buildings and creatures -- health
     *        * weather -- living time
     *        * resource -- amount of resource
     *        * tool -- durability
     */
    unsigned int health;

    /// Maximum amount of health.
    unsigned int max_health;

    /// Immortality.
    bool immortality;

    /// Angle of rotation.
    double angle;
};

#endif // OBJECT_H
