/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

class View;
class InputHandler;

#include "../View.h"
#include "../../common/BasicTypes.h"

class InputHandler
{
    bool key_was_pressed[GLFW_KEY_LAST+1];
    int mouse_wheel;
    View* view;

public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     */
    InputHandler(View* v);

    /**
     * @brief Destructor
     */
    ~InputHandler();

    bool isCharPressed(int c);

    /**
     * @brief Returns some enum indicating what action should be
     *        performed by View.
     */
    void handleKeys();

};

#endif // KEY_HANDLER_H
