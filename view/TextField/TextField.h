/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <string>
#include <GL/glc.h>
#include "../dev_glfw.h"

class TextField
{
    std::string content;
    double x;
    double y;
    double height;
    double width;
    bool hidden;
    double font_size;
    
#ifdef __glfw3_h__ 
    GLFWwindow window;
#endif

public:

    TextField(double x, double y, double width, double height, 
#ifdef __glfw3_h__
    GLFWwindow window = 0,
#endif
    std::string content = "");

    ~TextField();

    std::string getText();

    void setText(std::string content);

    void render();

    bool hitTest(double x, double y);

    void setHidden(bool hidden);
    bool isHidden();
};

#endif // TEXT_FIELD_H
