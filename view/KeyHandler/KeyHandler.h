/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

class View;
class KeyHandler;

#include "../../model/BasicTypes.h"
#include "../View.h"

class KeyHandler
{
    View* view;

public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     */
    KeyHandler(View* v);

    /**
     * @brief Destructor
     */
    ~KeyHandler();

    /**
     * @brief Returns some enum indicating what action should be
     *        performed by View.
     */
    void handleKeys();

};

#endif // KEY_HANDLER_H
