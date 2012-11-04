/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef BUILDING_H
#define BUILDING_H

#include "../Object.h"
#include "../Tool/Tool.h"
#include "../../ObjectHeap/ObjectHeap.h"

/**
 * @class Building
 * @brief Building class contains information about building such as objects
 *        inside (including creatures).
 */
class Building : public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    Building(unsigned int max_space, unsigned int max_health);

    /**
     * @brief Destructor.
     */
    ~Building();

    //**************************************************************************
    // ACTIONS ACCESSING.
    //**************************************************************************

    /**
     * @brief  Gets objects pending actions.
     * @return vector with pending actions.
     */
    std::vector <Action *> getActions();

    /**
     * @brief Receives message.
     * @param action    message
     */
    void receiveMessage(Action * action);

    //**************************************************************************
    // CONTENTS MANIPULATION.
    //**************************************************************************

    /**
     * @brief  Puts object inside building.
     * @param  object   object to put inside
     * @return success of the operation
     */
    bool putInside(Object * object);

    /**
     * @brief  Takes out object from building.
     * @param  object   object to take out
     * @return success of the operation
     */
    bool takeOut(Object * object);

    //**************************************************************************
    // REPAIRING.
    //**************************************************************************

    /**
     * @brief Repairs building (adds delta to building health).
     * @param delta health to add
     */
    void repair(unsigned int delta);

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief  Get the value of contents.
     * @return the value of contents
     */
    const ObjectHeap * getContents();

    /**
     * @brief  Get the value of free_space.
     * @return the value of free_space
     */
    unsigned int getFreeSpace();

    /**
     * @brief Set the value of max_space.
     * @param new_var the new value of max_space
     */
    void setMaxSpace(unsigned int new_var);

    /**
     * @brief  Get the value of max_space.
     * @return the value of max_space
     */
    unsigned int getMaxSpace();

    /**
     * @brief  Get the value of isFinished.
     * @return the value of isFinished
     */
    bool getCompleteness();

private:
    /// Building contents.
    ObjectHeap * contents;

    /// Free space.
    unsigned int free_space;
    /// Maximum available space.
    unsigned int max_space;

    /// @brief Completeness of the building. As building is founded, it gets 0
    ///        health. Building proccess is equivalent to repairing proccess.
    ///        After first repairing (as health becomes equals to max_health)
    ///        completeness value changes to true and building becomes complete.
    bool completeness;
};

#endif // BUILDING_H