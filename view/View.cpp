#include "View.h"
#include "../model/World/Object/Creatures/Creature.h"
#include "../model/World/Object/Creatures/Humanoid/Humanoid.h"

#include "../common/Log/Log.h"

#define VIEW_CAM_SIZE               8

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

View::View(const IWorld& w)
{
    initWindow();

    loadTextures();

    glfwGetWindowSize(&this -> width,
                      &this -> height);

    paused = false;
    reset = false;
    focus = NULL;
    console_input = "";

    this -> view_world = new ViewWorld(w, this -> width, this -> height);
    this -> input_handler = new InputHandler(this);

    this -> glc_context = glcGenContext();
    glcContext(this -> glc_context);

    this -> font = glcGenFontID();
    glcNewFontFromFamily(this -> font, "Liberation Mono");
    glcFontFace(this -> font, "Regular");
    glcFont(this -> font);

    this -> addInterfaceObject(new TextField(VIEW_CAM_SIZE/2-10.0, -getMaxScrY(), 10.0, 0.5
#ifdef __glfw3_h__
    ,window
#endif
    ));

    sel_info = new TextField(getMaxScrX() - 7.0, getMaxScrY() - 4.0, 7.0, 4.0
#ifdef __glfw3_h__
    ,window
#endif
    );

    sel_info -> setFontSize(0.2);
    sel_info -> setLocked(true);
    this -> sel_info -> setHidden(true);

    this -> addInterfaceObject(this -> sel_info);

    this -> setFocus( rendered.at(0) );
}

View::~View()
{
    delete view_world;
    delete input_handler;

    for(uint i = 0; i < rendered.size(); i++)
    {
        delete rendered.at(i);
    }

    for(uint i = 0; i < texture_buf.size(); i++)
    {
        delete texture_buf.at(i);
    }

    glcDeleteFont(this -> font);

    glfwTerminate();
}

void View::loadTextures()
{
    uint flags = SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA;
    texture_buf.push_back(new ViewTexture("res/bar_empty.png", flags));
    texture_buf.push_back(new ViewTexture("res/bar_red.png",   flags));
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
    view_world -> setY(new_var);
}

double View::getMaxScrX()
{
    return VIEW_CAM_SIZE;
}

double View::getMaxScrY()
{
    return VIEW_CAM_SIZE * height/width;
}

void View::setDistance(double newdist)
{
    view_world -> setCamRad( ((double)VIEW_CAM_RADIUS) * newdist );
}


double View::getDistance()
{
    return view_world -> getCamRad() / VIEW_CAM_RADIUS;
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

void View::setUserInput(std::string input)
{
    this -> console_input = input;
}

std::string View::getUserInput()
{
    std::string temp = console_input;
    console_input = "";
    return temp;
}

bool mouse_clicked = false;

void View::redraw()
{
    // Check for an update of window dimensions
    glfwGetWindowSize(&this -> width,
                      &this -> height);

    // Tweak coordinate grid to correspond in screen dimension
    // changes.

    glViewport(0,0,width,height);

    // Handling screen presses

    input_handler->handleKeys();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0, 0, -1);

    view_world -> redraw();
    this -> displaySelectionInfo();

    int mouse_x, mouse_y;
    glfwGetMousePos(&mouse_x, &mouse_y);

    // Handling way of down-to-up openGL coordinates
    mouse_y = this -> height - mouse_y;

    // Screen X and Y
    double sx = ((double)mouse_x/width  - 0.5) * getMaxScrX() * 2;
    double sy = ((double)mouse_y/height - 0.5) * getMaxScrY() * 2;

    // World  X and Y
    double wx = view_world -> screenToWorldX( sx );
    double wy = view_world -> screenToWorldY( sy );

    const std::vector<const Object*> selection = view_world -> getViewObjectAt(wx, wy);

    if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !mouse_clicked)
    {
        mouse_clicked = true;
    }
    else if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && mouse_clicked)
    {
        if (selection.size() > 0)
        {
            std::cout << "=======Selection stats=========="
                      << std::endl;

            for (uint i = 0; i < selection.size(); ++i)
            {
                const Object* selected = selection.at(i);

                std::cout << "=======Selected object=========="
                          << std::endl;
                std::cout << selected -> printObjectInfo(true);
                        
            }

            this -> view_world -> setSelection(selection.at(0) -> getObjectID());
            this -> sel_info -> setHidden(false);
        }
        else
        {
            this -> view_world -> clearSelection();
            this -> sel_info -> setHidden(true);
        }

        mouse_clicked = false;
    }

    if (mouse_clicked)
    {
        bool focus_changed = false;

        this -> setFocus(NULL);

        for (uint i = 0; i < this -> rendered.size(); ++i)
        {
            if (rendered.at(i) -> hitTest(sx, sy) && !rendered.at(i) -> isLocked())
            {
                focus_changed = true;
                this -> setFocus(this -> rendered.at(i));
            }
        }

        if (!focus_changed)
        {
            // Draw a circle at cursor position

            glColor4d(0.0, 0.0, 0.0, 0.6);
            ViewUtilities::glCirclef_blend(sx, sy, view_world -> worldToScreenDist(1.0));
            glColor3d(1.0, 1.0, 1.0);
        }
    }

    if (selection.size() > 0)
    {
        const Object* obj = selection[0];

        double px = view_world -> worldToScreenX(obj -> getCoords().getX());
        double py = view_world -> worldToScreenY(obj -> getCoords().getY());
        double sz = view_world -> worldToScreenDist(obj -> getShape().getSize());

        drawProgressBar(px-sz, py + sz/4, sz*2,
                        (double)obj -> getHealthPoints() / obj -> getMaxHealthPoints());
    }


#ifdef VIEW_DEBUG
    if (display_grid)
    {
        // In debug mode, draw a grid over the screen.

        double xoff = -view_world -> worldToScreenX(0.0);
        double yoff = -view_world -> worldToScreenY(0.0);

        const double grid_size = getDistance() / VIEW_GRID_SIZE;

        xoff *= grid_size;
        yoff *= grid_size;

        xoff = xoff - (int)xoff;
        yoff = yoff - (int)yoff;

        xoff /= grid_size;
        yoff /= grid_size;

        int end = getMaxScrX() * getDistance();

        glBegin(GL_LINES);
        for (int i = -end; i <= end; i++)
        {
                double shift = (double)i / grid_size;

                glVertex2d(-getMaxScrX(),  shift - yoff);
                glVertex2d( getMaxScrX(),  shift - yoff);

                glVertex2d( shift - xoff, -getMaxScrY());
                glVertex2d( shift - xoff,  getMaxScrY());
        }
        glEnd();
    }

    // Drawing debug message at the top of the screen.

    glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
    ViewUtilities::glRectf_blend(-getMaxScrX(), getMaxScrY(), getMaxScrX(), getMaxScrY()-0.6f);
    glColor3f(1.0f, 1.0f, 1.0f);

    std::string msg = std::to_string(wx) + " " + std::to_string(wy) + " " + std::to_string(getDistance());
    if(this -> isPaused()) msg += " PAUSED";

    ViewUtilities::renderText(-getMaxScrX(), getMaxScrY() - 0.5, 24.f, msg);
#endif

    // Render interface objectsTextField* focus

    for (uint i = 0; i < rendered.size(); ++i)
    {
        rendered.at(i) -> render( rendered.at(i) == focus );
    }

    glLoadIdentity();
    glfwSwapBuffers();
}

void View::drawProgressBar(double x, double y, double width, double percent)
{
    double height = width/5;

    texture_buf[1] -> setTextureDimensions(0, 0, percent, 1.0);

    texture_buf[0] -> render(x, y, width,         height);
    texture_buf[1] -> render(x, y, width*percent, height);
}

void View::displaySelectionInfo()
{
    const Object* obj = this -> view_world -> getSelection();
    if(obj)
    {
        //this -> sel_info -> setText(printObjectViewInfo(obj));
        this -> sel_info -> setText(obj -> printObjectInfo(false));
    }
}

std::string View::printObjectViewInfo(const Object* obj)
{
    std::stringstream ss;

    switch(obj -> getType())
    {
        case RESOURCE:
        {
            const Resource* res = static_cast<const Resource*>(obj);
            switch(res -> getSubtype())
            {
                case RES_FOOD:
                    ss << "Grass?" << std::endl;
                    break;
                case RES_BUILDING_MAT:
                    ss << "Wood?" << std::endl;
                    break;
                default:
                    ss << "Resource" << std::endl;
                    break;
            }
            break;
        }
        case BUILDING:
            ss << "Building" << std::endl;
            break;
        case TOOL:
            ss << "Tool" << std::endl;
            break;
        case CREATURE:
        {
            const Creature* cr = static_cast<const Creature*>(obj);
            switch(cr -> getSubtype())
            {
                case HUMANOID:
                    // Display the name of certain humanoid.
                    ss << "Noname" << std::endl;

                    ss << "Human?" << std::endl;
                    break;
                case NON_HUMANOID:
                    ss << "Cow?" << std::endl;
                    break;
            }
            break;
        }
        default:
            ss << "You can't select weather, y'know?" << std::endl;
            break;
    }

//    ss << "\\HP "
//       << ((double)obj -> getHealthPoints()) / (obj -> getMaxHealthPoints())
//       << std::endl;

    return ss.str();
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

    glFrustum(-getMaxScrX(),
               getMaxScrX(),
              -getMaxScrY(),
               getMaxScrY(), 1, 50);
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

void View::addInterfaceObject(TextField *new_obj)
{
    rendered.push_back(new_obj);
}

//void View::addConsoleOutput(std::string app)
//{
//    std::string text = console -> getText();
//    console -> setText(text + "\n" + app);
//}
