#include "KeyHandler.h"

// TODO: Change name this define
#define SPEED 1

#ifdef __glfw3_h__
    #define glfwGetKey(key) glfwGetKey(view -> getWindow(), key)    
#endif

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
        if(glfwGetKey(GLFW_KEY_RIGHT))
        {
            view -> setX(view -> getX() + SPEED);
        }
        if(glfwGetKey(GLFW_KEY_LEFT))
        {
            view -> setX(view -> getX() - SPEED);
        }
        if(glfwGetKey(GLFW_KEY_DOWN))
        {
            view -> setY(view -> getY() - SPEED);
        }
        if(glfwGetKey(GLFW_KEY_UP))
        {
            view -> setY(view -> getY() + SPEED);
        }
        if(glfwGetKey('P') && key_was_pressed['P'] == false)
        {
            view -> setPaused(!view -> isPaused());
        }

        for(int i = 0; i < GLFW_KEY_LAST; ++i)
        {
            key_was_pressed[i] = glfwGetKey(i) ? true : false;
        }
}
