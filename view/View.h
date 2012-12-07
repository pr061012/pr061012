/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

#include "ViewWorld/ViewWorld.h"
#include "InputHandler/InputHandler.h"
#include "../common/BasicTypes.h"
#include "../common/BasicDefines.h"
#include "../model/World/IWorld.h"
#include "TextField/TextField.h"
#include "Utilities/ViewUtilities.h"

#include "TextureManager/TextureManager.h"
#include "TextureManager/Texture/Texture.h"

#include "dev_glfw.h"
#include <GL/glc.h>
#include <GL/gl.h>


/* VIEW_DEBUG turns on debug mode.
 * In debug mode, objects are rendered as circles.
 * BUILDING_MAT - green.
 * FOOD - red.
 * CREATURE - white.
 */


// TODO: I guess that would be adequate to replace TextField to some interface like IRenderable
//       that is going to be used by View and its inner classes.

class View
{
    /// World to be rendered by View.
    ViewWorld* view_world;

    /// Key handler for GUI
    InputHandler* input_handler;

    /// Texture manager
    TextureManager* texture_manager;

    /// Indicates, if world reset is necessary
    bool reset;

    /// GLC context used to render text
    GLint glc_context;
    GLint font;

    /// Object that is currently in focus. NULL if main window is in focus.
    TextField* focus;

    /// TextField that is displaying selection information
    TextField* sel_info;

    /// Console input send by user
    std::string console_input;

    /// Interface objects that are currently rendered by View
    std::vector<TextField*> rendered;

    /// Dimensions of program window, in pixels
    int width;
    int height;

#ifdef VIEW_DEBUG
public:
    /// Flag, indicating whether the grid should be displayed
    bool display_grid = false;
#endif

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

    /**
     * @brief Load textures that are going to be drawn into game interface.
     */
    void loadTextures();

private:
    bool paused;

public:
    //**************************************************************************
    // ACCESSORS
    //**************************************************************************

    Texture* getTexture(std::string name, int index = 0);

    /**
     * @brief Returns in-game x coordinate of camera center
     */
    double getX();
    /**
     * @brief Returns in-game y coordinate of camera center
     */
    double getY();

    /**
     * @brief Sets in-game x and y coordinates of game cam center
     */
    void setX(double new_var);
    void setY(double new_var);

    /**
     * @brief Returns max on-screen coordinates
     */
    double getMaxScrX();
    double getMaxScrY();

    void setDistance(double newdist);

    double getDistance();

    /**
     * @brief Sets game state to paused
     */
    void setPaused(bool new_state);

    /**
     * @brief Returns boolean value indicating if game state is set to paused
     */
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

//    void addConsoleOutput(std::string app);
#ifdef __glfw3_h__
    GLFWwindow getWindow();
#endif


    //**************************************************************************
    // DRAWING METHODS.
    //**************************************************************************

    /**
     * @brief Redraw currently displayed world.
     */
    void redraw();

    /**
     * @brief Draw a bar filled with certain percentage.
     * @param percent value from 0 to 1, indicating bar fullness
     */
    void drawProgressBar(double x, double y, double width, double percent = 1.0);

    void displaySelectionInfo();

    std::string printObjectViewInfo(const Object* obj);

    /**
     * @brief checks conditions to exit the program.
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
