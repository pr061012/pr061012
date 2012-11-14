/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_H
#define VIEW_H

#include <GL/glfw.h>
#include <GL/gl.h>
#include "../model/BasicTypes.h"
#include "../model/BasicDefines.h"
#include "../model/World/IWorld.h"
#include "ViewWorld/ViewWorld.h"
#include "KeyHandler/KeyHandler.h"
#include <iostream>

class View
{
    /// World to be rendered by View.
    ViewWorld* view_world;

    KeyHandler* key_handler;

    /// Key handler for GUI


public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     * @param w world that will be rendered by this class
     */
    View(const IWorld& w);

    /**
     * @brief Destructor
     */
    ~View();


    //**************************************************************************
    // ACCESSORS
    //**************************************************************************

    double getX();
    double getY();

    void setX(double new_var);
    void setY(double new_var);


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
    bool continues();

private:
    /**
     * @brief initialize graphics window
     */
    void initWindow();

};

#endif // VIEW_H
