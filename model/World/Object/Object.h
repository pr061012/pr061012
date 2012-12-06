/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "../Action/Action.h"
#include "../Message/Message.h"
#include "../../Utilities/Shape/Shape.h"
#include "../../../common/BasicTypes.h"
#include "../../../common/BasicDefines.h"
#include "../../../view/ViewObject/ViewObject.h"

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
     * @param type  ObjectType
     */
    Object(ObjectType type, bool solidity = true, bool movable = true,
           bool flyable = false, bool pickable = false,
           bool immortality = false);

    /**
     * @brief Destructor.
     */
    virtual ~Object();

    //**************************************************************************
    // OBJECT'S LIFE.
    //**************************************************************************

    /**
     * @brief  Gets objects pending actions.
     * @return vector with pending actions.
     */
    virtual std::vector<Action>* getActions() = 0;

    /**
     * @brief Receives message.
     */
    virtual void receiveMessage(Message message) = 0;

    //**************************************************************************
    // OBJECT'S INFORMATION.
    //**************************************************************************

    /**
     * @brief  Prints out object's information.
     * @param  full flag determing return complete information about object
     *              or not
     * @return string with information
     */
    virtual std::string printObjectInfo(bool full) const;

    //**************************************************************************
    // HEALING/DAMAGING.
    //**************************************************************************

    /**
     * @brief  Damages object.
     * @param  delta amount of damage
     * @return amount of done damage
     */
    virtual uint damage(uint delta) = 0;

    /**
     * @brief  Heals object.
     * @param  delta amount of healing
     * @return amount of done healing
     */
    virtual uint heal(uint delta) = 0;

    /**
     * @brief Gets current object's heatlh points.
     */
    virtual uint getHealthPoints() const = 0;

    /**
     * @brief Gets maximum possible object's health points.
     */
    virtual uint getMaxHealthPoints() const = 0;

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
    // SOLIDITY.
    //**************************************************************************

    /**
     * @brief Makes object solid.
     */
    void makeSolid();

    /**
     * @brief Makes object non-solid.
     */
    void makeNonSolid();

    /**
     * @brief  Returns true if object is solid.
     * @return is object solid or not
     */
    bool isSolid() const;

    //**************************************************************************
    // PICKABILITY.
    //**************************************************************************

    /**
     * @brief Makes object pickable.
     */
    void makePickable();

    /**
     * @brief Makes object non-pickable.
     */
    void makeNonPickable();

    /**
     * @brief  Returns true if object is pickable.
     * @return is object pickable or not
     */
    bool isPickable() const;

    //**************************************************************************
    // MOVABILITY.
    //**************************************************************************

    /**
     * @brief Makes object movable.
     */
    void makeMovable();

    /**
     * @brief Makes object immovable.
     */
    void makeImmovable();

    /**
     * @brief  Returns true if object is movable.
     * @return is object movable or not
     */
    bool isMovable() const;

    //**************************************************************************
    // ABILITY TO FLY.
    //**************************************************************************

    /**
     * @brief Makes object flyable.
     */
    void makeFlyable();

    /**
     * @brief Makes object non-flyable.
     */
    void makeNonFlyable();

    /**
     * @brief  Returns true if object is flyable.
     * @return is object flyable or not
     */
    bool isFlyable() const;

    //**************************************************************************
    // FLYING FLAG.
    //**************************************************************************

    /**
     * @brief Makes object currently flying.
     */
    void makeFlying();

    /**
     * @brief Makes object non-flying.
     */
    void makeNonFlying();

    /**
     * @brief  Returns true if object is currently flying.
     * @return is object currently flying or not
     */
    bool isCurrentlyFlying() const;

    //**************************************************************************
    // DANGER.
    //**************************************************************************

    /**
     * @brief  Gets object's danger level.
     * @return danger level
     */
    uint getDangerLevel() const;

    /**
     * @brief Sets object's danger level.
     * @param danger_level  new danger level
     */
    void setDangerLevel(uint danger_level);

    //**************************************************************************
    // WEIGHT.
    //**************************************************************************

    /**
     * @brief  Gets object's weight.
     * @return weight
     */
    uint getWeight() const;

    /**
     * @brief Sets object's weight.
     * @param weight    new weight
     */
    void setWeight(uint weight);

    //**************************************************************************
    // NORMAL SPEED.
    //**************************************************************************

    /**
     * @brief  Gets object's normal speed.
     * @return normal speed
     */
    double getNormalSpeed() const;

    /**
     * @brief Sets object's normal speed.
     * @param speed     new normal speed
     */
    void setNormalSpeed(double speed);

    //**************************************************************************
    // OBJECT TYPE AND ID.
    //**************************************************************************

    /**
     * @brief  Gets the value of type.
     * @return the value of type
     */
    ObjectType getType() const;

    /**
     * @brief  Gets type's name.
     * @return the name of the type
     */
    virtual std::string getTypeName() const = 0;

    /**
     * @brief  Returns object's ID.
     * @return object's ID.
     */
    uint getObjectID() const;

    //**************************************************************************
    // OBJECT SHAPE, ANGLE AND COORDINATES.
    //**************************************************************************

    /**
     * @brief Sets object's shape type.
     * @param type  shape type
     */
    void setShapeType(ShapeType type);

    /**
     * @brief Sets object's shape size.
     * @param size  shape size
     */
    void setShapeSize(double size);

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
     * @brief Set object's coordinates
     * @param coords  new coordinates
     */
    void setCoords(const Vector& coords);

    /**
     * @brief  Get object's coordinates
     * @return object's coordinates
     */
    const Vector& getCoords() const;

    //**************************************************************************
    // CAST OPERATORS.
    //**************************************************************************

    /**
     * @brief Operator to cast an Object to const ViewObject.
     */
    operator const ViewObject();

private:
    //**************************************************************************
    // IDS.
    //**************************************************************************

    static uint CURRENT_ID;

    const uint id;

    //**************************************************************************
    // OBJECT'S INFORMATION.
    //**************************************************************************

    /// Object's type.
    const ObjectType type;

    /// Object's coordinates and shape.
    Shape shape;

    /// Angle of rotation.
    double angle;

    /// Object's danger level.
    uint danger_level;

    /// Object's weight.
    uint weight;

    /// Object's normal_speed.
    double normal_speed;

    //**************************************************************************
    // PROPERTIES FLAGS.
    //**************************************************************************

    /// Is object destroyed or not.
    bool destroyed;

    /// Immortality.
    bool immortality;

    /// Whether object is passable or not.
    bool solidity;

    /// Is it possible to pick up this object or not.
    bool pickable;

    /// Can this object move (or can someone move it) or not.
    bool movable;

    /// Can this object fly or not.
    bool flyable;

    /// Is this object currently flying or not. (Have sence only for objects
    /// with flyable == true flag).
    bool is_currently_flying;

protected:
    /// Array with actions.
    std::vector <Action> actions;

    //**************************************************************************
    // AUXILIARY METHODS.
    //**************************************************************************

    /**
     * @brief  Returns string in style: str<...spaces...>. Amount of spaces is
     *         equal to indent - str.size().
     * @param  str  string
     * @return string with spaces
     */
    std::string insertSpaces(std::string str, uint indent = OBJ_INFO_INDENT) const;
};

#endif // OBJECT_H
