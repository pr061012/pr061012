#include "KeyHandler.h"

// TODO: Change name this define
#define SPEED 1

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

KeyHandler::KeyHandler(View* v):
    view(v)
{

}

KeyHandler::~KeyHandler()
{

}

void KeyHandler::handleKeys()
{
        if (glfwGetKey(GLFW_KEY_RIGHT))
        {
            view -> setX(view -> getX() + SPEED);
        }

        if (glfwGetKey(GLFW_KEY_LEFT))
        {
            view -> setX(view -> getX() - SPEED);
        }

        if (glfwGetKey(GLFW_KEY_DOWN))
        {
            view -> setY(view -> getY() - SPEED);
        }

        if (glfwGetKey(GLFW_KEY_UP))
        {
            view -> setY(view -> getY() + SPEED);
        }
}
