/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef WINDOW_H
#define WINDOW_H

#include "../../Object/Object.h"
#include "../../ObjectHeap/ObjectHeap.h"

/**
 * @class Window
 *
 */
class Window
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

	/**
     * @brief Constructor.
	 */
    Window();

	/**
     * @brief Destructor.
	 */
    ~Window();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Set the value of parent.
     * @param new_var   the new value of parent
     */
    void setParent(Object * new_var);

    /**
     * @brief Get the value of parent.
     * @return the value of parent
     */
    Object * getParent();

    /**
     * @brief Set the value of contents.
     * @param new_var   the new value of contents
     */
    void setContents(ObjectHeap new_var);

    /**
     * @brief Get the value of contents.
     * @return the value of contents
     */
    ObjectHeap getContents();

private:
    /// Object-parent of this window.
	Object * parent;

    /// View from window.
	ObjectHeap contents;
};

#endif // WINDOW_H
