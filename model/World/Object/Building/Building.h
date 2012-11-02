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
    Building();

    /**
     * @brief Destructor.
     */
    ~Building();

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
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief  Get the value of contents.
     * @return the value of contents
     */
    const ObjectHeap * getContents();

    // TODO: Do we need that? Seems like to be a pretty bad thing.
    /**
     * @brief Set the value of free_space.
     * @param new_var the new value of free_space
     */
    void setFreeSpace(int new_var);

    /**
     * @brief  Get the value of free_space.
     * @return the value of free_space
     */
    int getFreeSpace();

    /**
     * @brief Set the value of max_space.
     * @param new_var the new value of max_space
     */
    void setMaxSpace(int new_var);

    /**
     * @brief  Get the value of max_space.
     * @return the value of max_space
     */
    int getMaxSpace();

    /**
     * @brief Set the value of completeness.
     * @param new_var the new value of completeness
     */
    void setCompleteness(bool new_var);

    /**
     * @brief  Get the value of isFinished.
     * @return the value of isFinished
     */
    bool getCompleteness();

private:
    /// Building contents.
    ObjectHeap * contents;

    /// Free space.
    int free_space;
    /// Maximum available space.
    int max_space;

    /// @brief Completeness of the building. As building is founded, it gets 0
    ///        health. Building proccess is equivalent to repairing proccess.
    ///        After first repairing (as health becomes equals to max_health)
    ///        completeness value changes to true and building becomes complete.
    bool completeness;
};

#endif // BUILDING_H
