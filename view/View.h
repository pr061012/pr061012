/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_H
#define VIEW_H

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#include <GL/glfw.h>
#include <GL/gl.h>
#include "SOIL.h"
#include "../model/BasicTypes.h"
#include "../model/World/IWorld.h"
#include "ViewWorld/ViewWorld.h"
#include <iostream>

class View
{
    ViewWorld* view_world;

public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     */
    View(IWorld* w);

    /**
     * @brief Destructor
     */
    ~View();

    void redraw();

    /**
     * @brief returns exit condition
     */
    bool isExit();

private:
    // TODO: Move this method to GUI?
    void initWindow();

};

#endif // VIEW_H
