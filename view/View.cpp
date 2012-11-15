#include "View.h"

#define VIEW_DEBUG

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
    glTranslatef(0.0f, 0.0f, -2*VIEW_CAM_SCALE);

    view_world->redraw();

#ifdef VIEW_DEBUG
    double xoff = view_world->getX();
    double yoff = view_world->getY();

    xoff /= VIEW_CAM_SCALE;
    yoff /= VIEW_CAM_SCALE;

    xoff = (xoff - (int)xoff)*VIEW_CAM_SCALE;
    yoff = (yoff - (int)yoff)*VIEW_CAM_SCALE;

    glBegin(GL_LINES);
    for(int i = -VIEW_CAM_SCALE-2; i < VIEW_CAM_SCALE+2; i++)
    {
        glVertex2d(-10.0 + xoff,  i + yoff);
        glVertex2d( 10.0 + xoff,  i + yoff);

        glVertex2d( i + xoff, -10.0 + yoff);
        glVertex2d( i + xoff,  10.0 + yoff);
    }
    glEnd();
#endif

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
        std::cerr << "Window initialized unsuccesfully.";
    }

    glMatrixMode(GL_PROJECTION); // editing projection params
    glLoadIdentity();

    float aspect_ratio = ((float)VIEW_SCREEN_HEIGHT) / VIEW_SCREEN_WIDTH;

    glFrustum(-.5, .5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
    glMatrixMode(GL_MODELVIEW);

    glfwSetWindowTitle("Project 0612");
}

bool View::continues()
{
    return !glfwGetKey(GLFW_KEY_ESC)
            && glfwGetWindowParam(GLFW_OPENED);
}
