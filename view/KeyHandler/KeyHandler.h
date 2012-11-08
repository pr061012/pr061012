/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#include "../../model/BasicTypes.h"

class KeyHandler
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     */
    KeyHandler();

    /**
     * @brief Destructor
     */
    ~KeyHandler();

    /**
     * @brief Returns some enum indicating what action should be
     *        performed by View.
     */
    int handleKeys();

};

#endif // KEY_HANDLER_H
