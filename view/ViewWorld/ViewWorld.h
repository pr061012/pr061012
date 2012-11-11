/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_WORLD_H
#define VIEW_WORLD_H

#include "../../model/BasicTypes.h"
#include "../../model/BasicDefines.h"
#include "../../model/World/IWorld.h"
#include "../../model/World/Object/Object.h"
#include <GL/glfw.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

class ViewWorld
{
    /// World that is rendered by this class
    IWorld* world;

public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     * @param w world to render
     */
    ViewWorld(IWorld* w);

    /**
     * @brief Destructor
     */
    ~ViewWorld();

private:
    //**************************************************************************
    // TEXTURE LOADING.
    //**************************************************************************

    /// array of loaded textures
    GLuint texture_buf[2];

    /**
     * @brief preload game textures in openGL
     */
    void loadTextures();

private:
    //**************************************************************************
    // DRAWING METHODS.
    //**************************************************************************

    /// X and Y coordinates of center of the game cam
    double x;
    double y;

    /// number of frames drawn
    int frame;

    /**
     * @brief draws specific object relative to current coordinates
     */
    void renderObject(Object* object); // TODO: Object -> ViewObject

    /**
     * @brief render a grass background all over the window
     */
    void renderBackground();

public:
    /**
     * @brief redraw background and all objects in range of
     *        the game camera
     */
    void redraw();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief set coordinates of center of the game cam
     */
    void setX(double new_var);
    void setY(double new_var);

};

#endif // VIEW_WORLD_H
