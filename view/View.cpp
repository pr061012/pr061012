#include "View.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

View::View(IWorld* w)
{
    if(!w)
    {
        std::cerr << "NULL World provided";
    }

    initWindow();

    view_world = new ViewWorld(w);
}



View::~View()
{
    delete view_world;
    glfwTerminate();
}

void View::redraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0.0f, 0.0f, -16.0f);

    // std::cout << "World successfully redrawn" << std::endl;
    view_world->redraw();

    glLoadIdentity();
    glfwSwapBuffers();
}

void View::initWindow()
{
    glfwInit();

    if( !glfwOpenWindow( SCREEN_WIDTH, SCREEN_HEIGHT,
                         0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
    {
        glfwTerminate();
        std::cerr << "[View] Window initialized unsuccesfully.";
    }

    glfwSetWindowTitle("Project 0612");

    glMatrixMode(GL_PROJECTION); // editing projection params
    glLoadIdentity();
    float aspect_ratio = ((float)SCREEN_HEIGHT) / SCREEN_WIDTH;
    glFrustum(-.5, .5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
    glMatrixMode(GL_MODELVIEW);
}

bool View::isExit()
{
    return !glfwGetKey(GLFW_KEY_ESC)
            && glfwGetWindowParam(GLFW_OPENED);
}
