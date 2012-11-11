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

int KeyHandler::handleKeys()
{
    if(glfwGetKey(GLFW_KEY_RIGHT))
    {
        view->setX(view->getX()+0.05);
    }

}
