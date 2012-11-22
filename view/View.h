/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_H
#define VIEW_H

#include "dev_glfw.h"
#include <GL/gl.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

#include "ViewWorld/ViewWorld.h"
#include "KeyHandler/KeyHandler.h"
#include "../common/BasicTypes.h"
#include "../common/BasicDefines.h"
#include "../model/World/IWorld.h"
#include "TextField/TextField.h"

#include <GL/glc.h>


/* VIEW_DEBUG turns on debug mode.
 * In debug mode, objects are rendered as circles.
 * BUILDING_MAT - green.
 * FOOD - red.
 * CREATURE - white.
 */

class View
{
    /// World to be rendered by View.
    ViewWorld* view_world;

    /// Key handler for GUI
    KeyHandler* key_handler;

    /// Indixates, whether world should be reset
    bool reset;

    /// GLC context used to render text
    GLint glc_context;
    GLint font;

    /// Object that is currently in focus. NULL if main window is in focus.
    TextField* focus;

    /// TextField that is used as a debug console
    TextField* console;
    /// Console input send by user
    std::string console_input;

    /// Interface objects that are currently rendered by View
    std::vector<TextField*> rendered;

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

private:
    bool paused;

public:
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

    /**
     * @brief Sets game state to paused
     */
    void setPaused(bool new_state);
    bool isPaused();

    /**
     * @brief Sets variable, whether world should be reset
     */
    void setReset(bool reset);
    /**
     * @brief Returns boolean value, if world should be reset
     */
    bool isReset();

    TextField* const getFocus();

    void setFocus(TextField* focus);

    void setUserInput(std::string input);

    /**
     * @brief Returns user console input
     */
    std::string getUserInput();

    void addConsoleOutput(std::string app);
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

    void addInterfaceObject(TextField* new_obj);

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
