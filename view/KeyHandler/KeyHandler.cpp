#include "KeyHandler.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

KeyHandler::KeyHandler(View* v)
{
    view = v;
}


KeyHandler::~KeyHandler()
{

}

// TODO: add 'speed' constant or variable instead of 0.05.
void KeyHandler::handleKeys()
{
        if(glfwGetKey(GLFW_KEY_RIGHT))
        {
            if(view->getX()+0.05 < VIEW_SCREEN_WIDTH)
            {
                view->setX(view->getX()+0.05);
            }
        }
        if(glfwGetKey(GLFW_KEY_LEFT))
        {
            if(view->getX()-0.05 > 0)
            {
                view->setX(view->getX()-0.05);
            }
        }
        if(glfwGetKey(GLFW_KEY_DOWN))
        {
            if(view->getY()-0.05 > 0)
            {
                view->setY(view->getY()-0.05);
            }
        }
        if(glfwGetKey(GLFW_KEY_UP))
        {
            if(view->getY()+0.05 < VIEW_SCREEN_HEIGHT)
            {
                view->setY(view->getY()+0.05);
            }
        }

}
