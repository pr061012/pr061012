#include "View.h"

#include "../common/Log/Log.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

View::View(const IWorld& w)
{
    initWindow();

    view_world = new ViewWorld(w);
    key_handler = new KeyHandler(this);
}

View::~View()
{
    delete view_world;
    delete key_handler;

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

#ifdef __glfw3_h__
GLFWwindow View::getWindow()
{
    return this -> window;
}
#endif

void View::setX(double new_var)
{
    view_world->setX(new_var);
}

void View::setY(double new_var)
{
    new_var = new_var > 0 ? new_var : 0;
    view_world->setY(new_var);
}

void View::redraw()
{
    key_handler->handleKeys();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0, 0, -2*VIEW_CAM_SIZE);

    view_world->redraw();

#ifdef VIEW_DEBUG
    double xoff = view_world->getX();
    double yoff = view_world->getY();

    xoff /= VIEW_CAM_SIZE;
    yoff /= VIEW_CAM_SIZE;

    xoff = (xoff - (int)xoff);
    yoff = (yoff - (int)yoff);

    glBegin(GL_LINES);
    for(int i = -VIEW_CAM_SIZE; i <= VIEW_CAM_SIZE; i++)
    {
        glVertex2d(-10.0,  i - yoff);
        glVertex2d( 10.0,  i - yoff);

        glVertex2d( i - xoff, -10.0);
        glVertex2d( i - xoff,  10.0);
    }
    glEnd();
#endif

    glLoadIdentity();
    glfwSwapBuffers();
}

void View::initWindow()
{
    glfwInit();
//    glfwWindowHint(GLFW_DEPTH_BITS, 16);
//    if(!(this -> window = glfwCreateWindow(VIEW_SCREEN_WIDTH, VIEW_SCREEN_HEIGHT,
//                         GLFW_WINDOWED, "Project", NULL)))
    if (!createWindow(VIEW_SCREEN_WIDTH, VIEW_SCREEN_HEIGHT))
    {
        glfwTerminate();
        Log::ERROR("Window initialized unsuccesfully.");
    }

    createContext();

    glMatrixMode(GL_PROJECTION); // editing projection params
    glLoadIdentity();

    float aspect_ratio = ((float)VIEW_SCREEN_HEIGHT)/VIEW_SCREEN_WIDTH;

    glFrustum(-.5, .5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
    glMatrixMode(GL_MODELVIEW);

    glfwSetWindowTitle("Project 0612");

    // needed for making OpenGl context, so glGetString does not return
    // NULL and SOIL funcs don't corrupt memory
    //glLoadIdentity();

}

bool View::continues()
{
    return ! glfwGetKey(GLFW_KEY_ESC) 
            && windowOpened();
}
