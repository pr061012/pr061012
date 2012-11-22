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

    if(!view -> getFocus())
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
        if(glfwGetKey('R') && key_was_pressed['R'] == false)
        {
            view -> setReset(true);
        }

        for(int i = 0; i < GLFW_KEY_LAST; ++i)
        {
            key_was_pressed[i] = glfwGetKey(i) ? true : false;
        }
    }
    else
    {
        TextField* focus = view -> getFocus();
        char tempChar = '\0';
        for(char c = 'A'; c<='Z'; ++c)
        {
            if(glfwGetKey(c))
            {
                if(!glfwGetKey(GLFW_KEY_LSHIFT) && !glfwGetKey(GLFW_KEY_RSHIFT))
                {
                    // Convert pressed char to lower case
                    tempChar = c - 'A' + 'a';
                }
                else tempChar = c;
            }
        }
        // Print symbol that is pressed last by index.
        if(tempChar != '\0') focus -> setText(focus -> getText() + tempChar);
    }
}
