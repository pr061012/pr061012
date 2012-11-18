#include "View.h"

#include "../common/Log/Log.h"

#define VIEW_CAM_SIZE               8

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

View::View(const IWorld& w)
{
    initWindow();

    paused = false;

    this -> view_world = new ViewWorld(w);
    this -> key_handler = new KeyHandler(this);

    this -> glc_context = glcGenContext();
    glcContext(this -> glc_context);

    this -> font = glcGenFontID();
    glcNewFontFromMaster(this -> font, 0);

    glcFont(this -> font);
    glcScale(24.f, 24.f);
}

View::~View()
{
    delete view_world;
    delete key_handler;

    glcDeleteFont(this -> font);

    glfwTerminate();
}

double View::getX()
{
    return view_world -> getX();
}

double View::getY()
{
    return view_world -> getY();
}

#ifdef __glfw3_h__
GLFWwindow View::getWindow()
{
    return this -> window;
}
#endif

void View::setX(double new_var)
{
    view_world -> setX(new_var);
}

void View::setY(double new_var)
{
    new_var = new_var > 0 ? new_var : 0;
    view_world -> setY(new_var);
}

void View::setPaused(bool new_state)
{
    paused = new_state;
}

bool View::isPaused()
{
    return paused;
}

bool mouse_clicked = 0;

void View::redraw()
{
    // Check for an update of window dimensions
    glfwGetWindowSize(&this -> width,
                      &this -> height);

    key_handler->handleKeys();

    int mouse_x, mouse_y;
    glfwGetMousePos(&mouse_x, &mouse_y);

     // Handling way of down-to-up openGL coordinates
    mouse_y = height - mouse_y;

    double wx = view_world -> screenToWorldX( ((double)mouse_x/width  - 0.5) * VIEW_CAM_SIZE * 2 );
    double wy = view_world -> screenToWorldY( ((double)mouse_y/height - 0.5) * VIEW_CAM_SIZE * 2 );

    if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !mouse_clicked)
    {
        mouse_clicked = 1;

        const std::vector<const Object*> selection = view_world -> getViewObjectAt(wx, wy);
        if(selection.size()>0)
        {
            const Object* selected = selection.at(0);

            std::cout << "=======  Coordinates  =========="
                      << std::endl;
            std::cout << "screen_center-world_x = " << this -> getX()
                      << std::endl;
            std::cout << "screen_center-world_y = " << this -> getY()
                      << std::endl;
            std::cout << "cursor-world_y = " << this -> getY()
                      << std::endl;

            std::cout << "=======Selected object=========="
                      << std::endl;
            std::cout << "type = " << selected -> getType()
                      << std::endl;
        }
    }
    else if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && mouse_clicked)
    {
        mouse_clicked = 0;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0, 0, -2*VIEW_CAM_SIZE);

    view_world -> redraw();

#ifdef VIEW_DEBUG
    // In debug mode, draw a grid over the screen.

    double xoff = view_world -> worldToScreenX(0.0);
    double yoff = view_world -> worldToScreenY(0.0);

    xoff = -(xoff - (int)xoff);
    yoff = -(yoff - (int)yoff);

    glBegin(GL_LINES);
    for(int i = -VIEW_CAM_SIZE; i <= VIEW_CAM_SIZE; i++)
    {
        glVertex2d(-VIEW_CAM_SIZE,  i - yoff);
        glVertex2d( VIEW_CAM_SIZE,  i - yoff);

        glVertex2d( i - xoff, -VIEW_CAM_SIZE);
        glVertex2d( i - xoff,  VIEW_CAM_SIZE);
    }
    glEnd();

    // Drawing debug message at the top of the screen.
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(-VIEW_CAM_SIZE, VIEW_CAM_SIZE, VIEW_CAM_SIZE, VIEW_CAM_SIZE-2.6f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-VIEW_CAM_SIZE, VIEW_CAM_SIZE - 2.5f);

    std::string msg = std::to_string(wx) + " " + std::to_string(wy);
    if(this -> isPaused()) msg += " PAUSED";

    glcRenderString( msg.c_str() );
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

    glfwGetWindowSize(&this -> width,
                      &this -> height);

    createContext();

    glMatrixMode(GL_PROJECTION); // editing projection params
    glLoadIdentity();

    float aspect_ratio = ((float)height)/width;

    glFrustum(-.5, .5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
    glMatrixMode(GL_MODELVIEW);

    glfwSetWindowTitle("Project 0612");

    // needed for making OpenGl context, so glGetString does not return
    // NULL and SOIL funcs don't corrupt memory
    glLoadIdentity();

    glfwSwapBuffers();
}

bool View::continues()
{
    return ! glfwGetKey(GLFW_KEY_ESC) 
            && windowOpened();
}
