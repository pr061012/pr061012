/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef WORLD_RENDERER_H
#define WORLD_RENDERER_H

#define CAM_RADIUS 30
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#include "../model/BasicTypes.h"
#include "../model/World/IWorld.h"
#include "../model/World/Object/Object.h"
#include <time.h>
#include <GL/glfw.h>
#include <GL/gl.h>
#include "SOIL.h"

class WorldRenderer
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     * @param world world to render
     */
    WorldRenderer(IWorld* w);

    /**
     * @brief Destructor
     */
    ~WorldRenderer();

    void drawingLoop();

private:
    GLuint texture_buf[2];

    void loadTextures();


    /// World that is rendered by this class
    IWorld* world;

    /// X and Y coordinates of center of the game cam
    double x;
    double y;

    int frame;
    int delay;

public:

    void step();

private:

    void drawImage();

    void renderObject(Object* object);

    void renderBackground();
//    void renderGUI(GUI& gui);
//    void handleKeyPress();

    bool WorldRenderer::isExit();

};

#endif // WORLD_RENDERER_H
