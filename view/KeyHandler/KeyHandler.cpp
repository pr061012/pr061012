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
        if(glfwGetKey('P') && !key_was_pressed['P'])
        {
            view -> setPaused(!view -> isPaused());
        }
        if(glfwGetKey('R') && !key_was_pressed['R'])
        {
            view -> setReset(true);
        }
    }
    else
    {
        TextField* focus = view -> getFocus();
        if(glfwGetKey(GLFW_KEY_BACKSPACE) && !key_was_pressed[GLFW_KEY_BACKSPACE])
        {
            std::string text = focus -> getText();
            if(text.length() > 0)
            {
                focus -> setText( text.erase(text.length()-1) );
            }
        }
        else if(glfwGetKey(GLFW_KEY_ENTER) && !key_was_pressed[GLFW_KEY_ENTER])
        {
            view -> setUserInput(focus -> getText());
            focus -> setText("");
        }
        else
        {
            char tempChar = '\0';
            for(int c = 'A'; c<='Z'; ++c)
            {
                if(glfwGetKey(c) && !key_was_pressed[c])
                {
                    if(!glfwGetKey(GLFW_KEY_LSHIFT) && !glfwGetKey(GLFW_KEY_RSHIFT))
                    {
                        // Convert pressed char to lower case
                        tempChar = c - 'A' + 'a';
                    }
                    else tempChar = c;
                }
            }
            for(int c = '0'; c<='9'; ++c)
            {
                if(glfwGetKey(c) && !key_was_pressed[c])
                {
                    tempChar = c;
                }
            }
            if(glfwGetKey(GLFW_KEY_SPACE) && !key_was_pressed[GLFW_KEY_SPACE])
            {
                tempChar = ' ';
            }

            // Print symbol that is pressed last by index.
            if(tempChar != '\0') focus -> setText(focus -> getText() + tempChar);
        }
    }

    for(int i = 0; i < GLFW_KEY_LAST; ++i)
    {
        key_was_pressed[i] = glfwGetKey(i) ? true : false;
    }
}
