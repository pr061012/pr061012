/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_H
#define VIEW_H

// GLFW 3.0 check
#ifdef USE_GLFW3
    #include <GL/glfw3.h>
#else
    #include <GL/glfw.h>
#endif

#include <GL/gl.h>
#include <iostream>

#include "ViewWorld/ViewWorld.h"
#include "KeyHandler/KeyHandler.h"
#include "../common/BasicTypes.h"
#include "../common/BasicDefines.h"
#include "../model/World/IWorld.h"

#include <GL/glc.h>

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
    #define glfwGetWindowSize(width, height) glfwGetWindowSize(_VIEW_WINDOW, width, height)
    #define glfwGetMousePos(x,y)    glfwGetCursorPos(_VIEW_WINDOW, x,y)
    #define glfwGetMouseButton(button) glfwGetMouseButton(_VIEW_WINDOW, button)
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

    /// Key handler for GUI
    KeyHandler* key_handler;

    /// GLC context used to render text
    GLint glc_context;
    GLint font;

    /// Dimensions of program window, in pixels
    int width;
    int height;

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

    /**
     * @brief Returns in-game x coordinate of camera center
     */
    double getX();
    /**
     * @brief Returns in-game y coordinate of camera center
     */
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
    bool continues();

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
