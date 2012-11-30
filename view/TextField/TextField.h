/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <string>
#include <GL/glc.h>
#include "../dev_glfw.h"
#include "../Utilities/ViewUtilities.h"

class TextField
{
    int render_steps;
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

    void render(bool in_focus = false);

    bool hitTest(double x, double y);

    void setHidden(bool hidden);
    bool isHidden();

    void setFontSize(double font_size);

    double getFontSize();
};

#endif // TEXT_FIELD_H
