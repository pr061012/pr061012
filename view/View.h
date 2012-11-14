/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_H
#define VIEW_H

#include <GL/glfw3.h>
#include <GL/gl.h>
//#include "config.h"
#include <SOIL/SOIL.h>
#include "../model/BasicTypes.h"
#include "../model/BasicDefines.h"
#include "../model/World/IWorld.h"
#include "ViewWorld/ViewWorld.h"
#include "KeyHandler/KeyHandler.h"
#include <iostream>

// Defines for glfw compatibility
#ifdef __glfw3_h__
    #define _VIEW_WINDOW window
    #define glfwSwapBuffers() glfwSwapBuffers(window); glfwPollEvents()
    #define createWindow(width, height)  (_VIEW_WINDOW = glfwCreateWindow(width, \
                            height, GLFW_WINDOWED, "Project", NULL))
    #define createContext() glfwMakeContextCurrent(_VIEW_WINDOW); \
                            glfwSetInputMode( window, GLFW_KEY_REPEAT, GL_TRUE )
    #define glfwSetWindowTitle(text) glfwSetWindowTitle(_VIEW_WINDOW, text)
    #define glfwGetKey(key) glfwGetKey(_VIEW_WINDOW, key)
    #define windowOpened() !glfwGetWindowParam(_VIEW_WINDOW, GLFW_CLOSE_REQUESTED)
#else

    #define createWindow(width, height)  glfwOpenWindow(width, height, \
                                           0, 0, 0, 0, 0, 0, GLFW_WINDOW)
    #define createContext() 
    #define windowOpened()  glfwGetWindowParam(GLFW_OPENED)
#endif

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
    View(IWorld* w);

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

#ifdef __glfw3_h__
    GLFWwindow getWindow();
#endif

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

#ifdef __glfw3_h__
    /// Window
    GLFWwindow window;
#endif

};

#endif // VIEW_H
