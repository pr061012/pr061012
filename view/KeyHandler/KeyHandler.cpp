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

bool KeyHandler::isCharPressed(int c)
{
    if(c >= 'A' && c <= 'Z')
    {
        if(!glfwGetKey(GLFW_KEY_LSHIFT) && !glfwGetKey(GLFW_KEY_RSHIFT))
        {
            return false;
        }
    }
    if(c >= 'a' && c <= 'z')
    {
        if(glfwGetKey(GLFW_KEY_LSHIFT) || glfwGetKey(GLFW_KEY_RSHIFT))
        {
            return false;
        }
        c = c - 'a' + 'A';
    }
    if(c == '_')
    {
        if(!glfwGetKey(GLFW_KEY_LSHIFT) && !glfwGetKey(GLFW_KEY_RSHIFT))
        {
            return false;
        }
        c = '-';
    }

    return glfwGetKey(c) && !key_was_pressed[c];
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
                if(isCharPressed(c)) tempChar = c;
                if(isCharPressed(c - 'A' + 'a')) tempChar = c - 'A' + 'a';
            }
            for(int c = '0'; c<='9'; ++c)
            {
                if(isCharPressed(c)) tempChar = c;
            }
            if(isCharPressed(' ')) tempChar = ' ';
            if(isCharPressed('.')) tempChar = '.';
            if(isCharPressed('-')) tempChar = '-';
            if(isCharPressed('_')) tempChar = '_';

            // Print symbol that is pressed last by index.
            if(tempChar != '\0') focus -> setText(focus -> getText() + tempChar);
        }
    }

    for(int i = 0; i < GLFW_KEY_LAST; ++i)
    {
        if(glfwGetKey(i) && !key_was_pressed[i])
        {
            std::cout << "pressed key: " << i << std::endl;
        }
        key_was_pressed[i] = glfwGetKey(i) ? true : false;
    }
}
