/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_OBJECT_H
#define VIEW_OBJECT_H

#include "../model/BasicTypes.h"

class ViewObject
{
    /// Type of rendered object
    ObjectType type;

    /// This variable tells what animation to render
    // ObjectState cur_state;

public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     */
    ViewObject();

    /**
     * @brief Destructor
     */
    ViewObject();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Set the type of current object.
     * @param new_var the new value of type
     */
    void setType(ObjectType new_var);

    /**
     * @brief Get the type of current object.
     * @return the value of type
     */
    ObjectType getType();

};

#endif // VIEW_OBJECT_H
