#include "View.h"

#include "../log/Log.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

View::View(IWorld* w)
{
    if(!w)
    {
        Log::ERROR("NULL World provided to View.");
    }

    initWindow();

    view_world = new ViewWorld(w);
    key_handler = new KeyHandler(this);
}



View::~View()
{
    delete view_world;
    glfwTerminate();
}

double View::getX()
{
    return view_world->getX();
}

double View::getY()
{
    return view_world->getY();
}

void View::setX(double new_var)
{
    new_var = new_var > 0 ? new_var : 0;
    //new_var = new_var < v ? new_var : 0;
    view_world->setX(new_var);
}

void View::setY(double new_var)
{
    view_world->setY(new_var);
}

void View::redraw()
{
    key_handler->handleKeys();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0.0f, 0.0f, -VIEW_CAM_SCALE*2);

    view_world->redraw();

    glLoadIdentity();
    glfwSwapBuffers();
}

void View::initWindow()
{
    glfwInit();

    if(!glfwOpenWindow(VIEW_SCREEN_WIDTH, VIEW_SCREEN_HEIGHT,
                         0, 0, 0, 0, 0, 0, GLFW_WINDOW))
    {
        glfwTerminate();
        Log::ERROR("Window initialized unsuccesfully.");
    }

    glMatrixMode(GL_PROJECTION); // editing projection params
    glLoadIdentity();

    float aspect_ratio = ((float)VIEW_SCREEN_HEIGHT) / VIEW_SCREEN_WIDTH;

    glFrustum(-.5, .5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
    glMatrixMode(GL_MODELVIEW);

    glfwSetWindowTitle("Project 0612");
}

bool View::isExit()
{
    return !glfwGetKey(GLFW_KEY_ESC)
            && glfwGetWindowParam(GLFW_OPENED);
}
