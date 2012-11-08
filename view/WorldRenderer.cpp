#include "WorldRenderer.h"

#include <iostream>

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

WorldRenderer::WorldRenderer(IWorld* w)
{
    glfwInit();

    if( !glfwOpenWindow( SCREEN_WIDTH, SCREEN_HEIGHT,
                         0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
    {
        glfwTerminate();
        //return -1;
        //throw some exception;
    }

    loadTextures();

    if( 0 == texture_buf[0] )
    {
        std::cerr<< "SOIL loading error:'" << SOIL_last_result() << "' \n";

    }

    glfwSetWindowTitle("Project 0612");

    glMatrixMode(GL_PROJECTION); // editing projection params
    glLoadIdentity();
    float aspect_ratio = ((float)SCREEN_HEIGHT) / SCREEN_WIDTH;
    glFrustum(-.5, .5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
    glMatrixMode(GL_MODELVIEW);

    world = w;
    x = 50.0;
    y = 50.0;

    frame = 0;
}

WorldRenderer::~WorldRenderer()
{
    glDeleteTextures( 1, texture_buf ); // Clearing textures created
}

void WorldRenderer::drawingLoop()
{
    do
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glRectd(-0.1, -0.1, 0.5, 0.5);
        glTranslatef(0.0f, 0.0f, -16.0f);
        step();

        glLoadIdentity();
        glfwSwapBuffers();

        // exit if ESC was pressed or window was closed
    } while(!glfwGetKey(GLFW_KEY_ESC)
            && glfwGetWindowParam(GLFW_OPENED));
}

void WorldRenderer::loadTextures()
{
    texture_buf[0] = SOIL_load_OGL_texture // Load an image file directly as a new OpenGL texture, using SOIL.
    (
        "../View/grass.png",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS
    );
}



void WorldRenderer::step()
{
    ++frame;

    renderBackground();

    Object** objects = world->getViewObjectsInRange
            (x, y, CAM_RADIUS);

    //std::cout << "Received objects for rendering." << std::endl;

    if(objects)
    {
        int i = 0;
        while( objects[i] != NULL )
        {
            renderObject( objects[i++] );
        }
    }

    //delete[] objects;
}

void WorldRenderer::redraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTranslatef(0.0f, 0.0f, -16.0f);
    renderBackground();


    glLoadIdentity();
    glfwSwapBuffers();
}

void WorldRenderer::drawImage()
{
}

void WorldRenderer::renderObject(Object* object)
{
    const Point &p = object->getCoords();

    double px = p.getX() - x;
    double py = p.getY() - y;

    glColor3f(1.0, 1.0, 0.0);

    px /= CAM_RADIUS;
    py /= CAM_RADIUS;
    px *= 8;
    py *= 8;
    glRectd(px-0.2, py-0.2, px+0.2, py+0.2);
}

void WorldRenderer::renderBackground()
{
    glBindTexture(GL_TEXTURE_2D, texture_buf[0]); // Choosing grass texture to render into the window

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the original
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glEnable(GL_TEXTURE_2D); // Entering texture drawing environment.

    glBegin(GL_POLYGON); // Texturing window frame with grass
        glTexCoord2f(0.0,   0.0); glVertex2f(-8.0f, -8.0f);
        glTexCoord2f(16.0,  0.0); glVertex2f( 8.0f, -8.0f);
        glTexCoord2f(16.0, 16.0); glVertex2f( 8.0f,  8.0f);
        glTexCoord2f(0.0,  16.0); glVertex2f(-8.0f,  8.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D); // Fun part is done for this frame, 2D textures are drawn.

    glColor3f(1.0f, 1.0f, 1.0f);
}

bool WorldRenderer::isExit()
{
    return !glfwGetKey(GLFW_KEY_ESC)
            && glfwGetWindowParam(GLFW_OPENED);
}
