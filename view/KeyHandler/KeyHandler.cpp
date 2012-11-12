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
            if (view -> getX() + SPEED < VIEW_SCREEN_WIDTH)
            {
                view -> setX(view -> getX() + SPEED);
            }
        }

        if (glfwGetKey(GLFW_KEY_LEFT))
        {
            if (view -> getX() - SPEED > 0)
            {
                view -> setX(view -> getX()-SPEED);
            }
        }

        if (glfwGetKey(GLFW_KEY_DOWN))
        {
            if (view -> getY() - SPEED > 0)
            {
                view -> setY(view -> getY() - SPEED);
            }
        }

        if (glfwGetKey(GLFW_KEY_UP))
        {
            if (view -> getY() + SPEED < VIEW_SCREEN_HEIGHT)
            {
                view -> setY(view -> getY() + SPEED);
            }
        }
}
