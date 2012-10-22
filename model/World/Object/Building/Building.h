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

    /**
     * @brief Builds or repaires building. Must be spawned only by tool.use();
     * @param tool
     */
    void maintain(Tool tool);

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    // TODO: Do we need this setter? We already have putInside() and takeOut()
    //       methods.
    /**
     * @brief Set the value of contents.
     * @param new_var the new value of contents
     */
    void setContents(ObjectHeap new_var);

    /**
     * @brief  Get the value of contents.
     * @return the value of contents
     */
    ObjectHeap getContents();

    // TODO: Do we need that? Seems like to be a pretty bad thing.
    /**
     * @brief Set the value of free_space.
     * @param new_var the new value of free_space
     */
    void setFreeSpace (int new_var);

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
     * @brief Set the value of isFinished.
     * @param new_var the new value of isFinished
     */
    void setIsFinished(bool new_var);

    /**
     * @brief  Get the value of isFinished.
     * @return the value of isFinished
     */
    bool getIsFinished();

private:
    // TODO: Maybe you should use ObjectHeap * instead of ObjectHeap. ObjectHeap
    //       may have enourmous size. It's obviously silly to copy big objects.
    /// Building contents.
    ObjectHeap contents;

    /// Free space.
    int free_space;
    /// Maximum available space.
    int max_space;

    /// Completeness of the building.
    bool isFinished;
};

#endif // BUILDING_H
