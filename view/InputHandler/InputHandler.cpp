#include "InputHandler.h"

// TODO: Change name this define
#define SPEED 1
#define VIEW_Z_SPEED 0.1

#ifdef __glfw3_h__
    #define glfwGetKey(key) glfwGetKey(view -> getWindow(), key)    
#endif

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

InputHandler::InputHandler(View* v):
    view(v)
{
#ifndef __glfw3_h__
    mouse_wheel = glfwGetMouseWheel();
#else
    mouse_wheel = 0;
#endif
}

InputHandler::~InputHandler()
{

}

bool InputHandler::isCharPressed(int c)
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

void InputHandler::handleKeys()
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
        if(glfwGetKey('P') && !key_was_pressed[static_cast<uint>('P')])
        {
            view -> setPaused(!view -> isPaused());
        }
        if(glfwGetKey('R') && !key_was_pressed[static_cast<uint>('R')])
        {
            view -> setReset(true);
        }

#ifdef VIEW_DEBUG
        if(glfwGetKey('G') && !key_was_pressed[static_cast<uint>('G')])
        {
            view -> display_grid = !view -> display_grid;
        }
#endif
#ifndef __glfw3_h__
        int tmp = glfwGetMouseWheel();
        if(mouse_wheel != tmp)
        {
            view -> setDistance(view -> getDistance() - VIEW_Z_SPEED * (tmp-mouse_wheel));
            mouse_wheel = tmp;
        }
#else
        double tmpx, tmpy;
        glfwGetScrollOffset(view -> getWindow(), &tmpx, &tmpy);
        if (tmpy)
        { 
            view -> setDistance(view -> getDistance() - VIEW_Z_SPEED * tmpy);
        }
#endif
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
        key_was_pressed[i] = glfwGetKey(i) ? true : false;
    }
}
