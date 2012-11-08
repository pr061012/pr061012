/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_WORLD_H
#define VIEW_WORLD_H

#define CAM_RADIUS 30

#include "../../model/BasicTypes.h"
#include "../../model/World/IWorld.h"
#include "../../model/World/Object/Object.h"
#include <GL/glfw.h>
#include <GL/gl.h>
#include "SOIL.h"

class ViewWorld
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     * @param world world to render
     */
    ViewWorld(IWorld* w);

    /**
     * @brief Destructor
     */
    ~ViewWorld();

private:
    GLuint texture_buf[2];

    void loadTextures();


    /// World that is rendered by this class
    IWorld* world;

    /// X and Y coordinates of center of the game cam
    double x;
    double y;

    int frame;

private:

    void renderObject(Object* object);

    void renderBackground();

public:
    void redraw();

    void setX(double new_var);
    void setY(double new_var);

};

#endif // VIEW_WORLD_H
