#include "WorldRenderer.h"

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

    glfwSetWindowTitle("Project 0612");

    glMatrixMode(GL_PROJECTION); // editing projection params
    glLoadIdentity();
    float aspect_ratio = ((float)SCREEN_HEIGHT) / SCREEN_WIDTH;
    glFrustum(-.5, .5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);

    world = w;
}

WorldRenderer::~WorldRenderer()
{

}

void WorldRenderer::drawingLoop()
{
    do
    {
        //step();
        //glClearColor3f(0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(1.0, 1.0, 0.0);
        glRectd(-0.1, -0.1, 0.1, 0.1);
        glLoadIdentity();
        glfwSwapBuffers();

        // exit if ESC was pressed or window was closed
    } while(!glfwGetKey(GLFW_KEY_ESC)
            && glfwGetWindowParam(GLFW_OPENED));
}



void WorldRenderer::step()
{
    Object** objects = world->getViewObjectsInRange
            (x, y, CAM_RADIUS);

    int i = 0;
    while( objects[i] )
    {
        renderObject( objects[i++] );
    }
}

void WorldRenderer::drawImage()
{
}

void WorldRenderer::renderObject(Object* object)
{
    Point p = object->getCoords();

    double px = p.getX() - x;
    double py = p.getY() - y;

    glRectd(px-0.15, py-0.15, px+0.15, py+0.15);
}
