/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_H
#define VIEW_H

#include <GL/glfw.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include "../model/BasicTypes.h"
#include "../model/BasicDefines.h"
#include "../model/World/IWorld.h"
#include "ViewWorld/ViewWorld.h"
#include <iostream>

class View
{
    /// World to be rendered by View.
    ViewWorld* view_world;

public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     * @param w world that will be rendered by this class
     */
    View(IWorld* w);

    /**
     * @brief Destructor
     */
    ~View();

    //**************************************************************************
    // DRAWING METHODS.
    //**************************************************************************

    /**
     * @brief Redraw currently displayed world
     */
    void redraw();

    /**
     * @brief checks conditions to exit the program
     * @return result of exit conditions
     */
    bool isExit();

private:
    /**
     * @brief initialize graphics window
     */
    void initWindow();

};

#endif // VIEW_H
