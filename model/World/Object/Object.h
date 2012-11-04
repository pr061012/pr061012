/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "../../Utilities/Shape/Shape.h"
#include "../../BasicTypes.h"
#include "../Action/Action.h"

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
     * @brief  Gets objects pending actions.
     * @return vector with pending actions.
     */
    virtual std::vector <Action> * getActions() = 0;

    /**
     * @brief Receives message.
     * @param action    message
     */
    // TODO: Uncomment when we need it.
    //virtual void receiveMessage(Action * action) = 0;

    //**************************************************************************
    // DESTROYED FLAG.
    //**************************************************************************

    /**
     * @brief Marks this object as destroyed.
     */
    void markAsDestroyed();

    /**
     * @brief  Returns true if object is destroyed.
     * @return is object destroyed or not
     */
    bool isDestroyed() const;

    //**************************************************************************
    // IMMORTALITY FLAG.
    //**************************************************************************

    /**
     * @brief Makes object mortal.
     */
    void makeMortal();

    /**
     * @brief Makes object immortal.
     */
    void makeImmortal();

    /**
     * @brief  Returns true if object is immortal.
     * @return is object immortal or not
     */
    bool isImmortal() const;

    //**************************************************************************
    // OBJECT TYPE.
    //**************************************************************************

    /**
     * @brief Get the value of type.
     * @return the value of type
     */
    ObjectType getType() const;

    //**************************************************************************
    // OBJECT SHAPE AND ANGLE.
    //**************************************************************************

    /**
     * @brief Set the value of shape.
     * @param new_var   the new value of shape
     */
    void setShape(Shape new_var);

    /**
     * @brief  Get the value of shape.
     * @return the value of shape
     */
    Shape getShape() const;

    /**
     * @brief Set the value of angle.
     * @param new_var   the new value of angle
     */
    void setAngle(double new_var);

    /**
     * @brief  Get the value of angle.
     * @return the value of angle
     */
    double getAngle() const;

    /**
     * @brief   Set object's coordinates
     * @param   coords  new coordinates
     */
    void setCoords(const Point& coords);

    /**
     * @brief   Get object's coordinates
     * @return  object's coordinates
     */
    const Point& getCoords() const;

private:
    /// Object's type.
    const ObjectType type;

    /// Object's coordinates and shape.
    Shape shape;

    /// Is object destroyed or not.
    bool destroyed;

    /// Immortality.
    bool immortality;

    /// Angle of rotation.
    double angle;

protected:
    /// Array with actions.
    std::vector <Action> actions;
};

#endif // OBJECT_H
