#include "View.h"

#include "../common/Log/Log.h"

#define VIEW_CAM_SIZE               8

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

View::View(const IWorld& w)
{
    initWindow();

    glfwGetWindowSize(&this -> width,
                      &this -> height);

    paused = false;
    reset = false;
    focus = NULL;

    this -> view_world = new ViewWorld(w, this -> width, this -> height);
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

void View::setReset(bool reset)
{
    this -> reset = reset;
}

bool View::isReset()
{
    return this -> reset;
}

TextField* const View::getFocus()
{
    return focus;
}

void View::setFocus(TextField* focus)
{
    this -> focus = focus;
}

bool mouse_clicked = 0;

void View::redraw()
{
    // Check for an update of window dimensions
    glfwGetWindowSize(&this -> width,
                      &this -> height);

    // Tweak coordinate grid to correspond in screen dimension
    // changes.

    glViewport(0,0,width,height);

    // Handling screen presses

    key_handler->handleKeys();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0, 0, -1);

    view_world -> redraw();

    int mouse_x, mouse_y;
    glfwGetMousePos(&mouse_x, &mouse_y);

    // Handling way of down-to-up openGL coordinates
    mouse_y = this -> height - mouse_y;

    // Screen X and Y
    double sx = ((double)mouse_x/width  - 0.5) * VIEW_CAM_SIZE * 2;
    double sy = ((double)mouse_y/height - 0.5) * VIEW_CAM_SIZE * 2 * height/width;
    // World  X and Y
    double wx = view_world -> screenToWorldX( sx );
    double wy = view_world -> screenToWorldY( sy );

    if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !mouse_clicked)
    {
        mouse_clicked = 1;
    }
    else if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && mouse_clicked)
    {
        const std::vector<const Object*> selection = view_world -> getViewObjectAt(wx, wy);
        if(selection.size() > 0)
        {
            std::cout << "=======Selection stats=========="
                      << std::endl;

            for(uint i = 0; i < selection.size(); ++i)
            {
                const Object* selected = selection.at(i);

                std::cout << "=======Selected object=========="
                          << std::endl;
                std::cout << "type = " << selected -> getType()
                          << std::endl;
                std::cout << "x = " << selected -> getCoords().getX()
                          << std::endl;
                std::cout << "y = " << selected -> getCoords().getY()
                          << std::endl;
            }
        }

        mouse_clicked = 0;
    }

    if(mouse_clicked)
    {
        double angle;
        double radius = view_world -> worldToScreenDist(1.0);

        glColor4d(0.0, 0.0, 0.0, 0.6);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBegin(GL_TRIANGLE_FAN);
            for(int i = 0; i < 100; i++) {
                angle = 2.0 * i * M_PI / 100;
                glVertex2d((sx + cos(angle) * radius),
                           (sy + sin(angle) * radius));
            }
        glEnd();

        glDisable(GL_BLEND);

        glColor4d(1.0,1.0,1.0,1.0);
    }

#ifdef VIEW_DEBUG
    // In debug mode, draw a grid over the screen.

    double xoff = -view_world -> worldToScreenX(0.0);
    double yoff = -view_world -> worldToScreenY(0.0);

    xoff = xoff - (int)xoff;
    yoff = yoff - (int)yoff;

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

    // Render interface objectsTextField* focus

    for(int i = 0; i < rendered.size(); ++i)
    {
        rendered[i]->render();
    }

    glLoadIdentity();
    glfwSwapBuffers();
}

void View::initWindow()
{
    glfwInit();

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

    glFrustum(-VIEW_CAM_SIZE,
               VIEW_CAM_SIZE,
              -VIEW_CAM_SIZE * aspect_ratio,
               VIEW_CAM_SIZE * aspect_ratio, 1, 50);
    glMatrixMode(GL_MODELVIEW);

    glfwSetWindowTitle("Project 0612");

    // needed for making OpenGl context, so glGetString does not return
    // NULL and SOIL funcs don't corrupt memory
    // glLoadIdentity();

    glfwSwapBuffers();
}

bool View::continues()
{
    return ! glfwGetKey(GLFW_KEY_ESC) 
            && windowOpened();
}
