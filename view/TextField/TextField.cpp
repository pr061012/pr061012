#include "TextField.h"

#define VIEW_CAM_SIZE               8


TextField::TextField(double x, double y, double width, double height, 
#ifdef __glfw3_h__
    GLFWwindow window,
#endif
      std::string content) : content(content),
          x(x), 
          y(y),
          height(height),
          width(width),
          hidden(false),
          font_size(height * 0.6)

#ifdef __glfw3_h__
    , window(window)
#endif
{
}

TextField::~TextField()
{
}

std::string TextField::getText()
{
    return this -> content;
}

void TextField::setText(std::string content)
{
    this -> content = content;
}

void TextField::render()
{
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glRectf(x, y, x+width, y+height);
    glDisable(GL_BLEND);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);

    int scr_width, scr_height;
    glfwGetWindowSize(&scr_width,
                      &scr_height);

    double scale = (double)scr_height / VIEW_CAM_SIZE * font_size;

    glcScale(scale, scale);
    glcRenderString( content.c_str() );
    glcScale(1.0/scale, 1.0/scale);
}

bool TextField::hitTest(double x, double y)
{
    x -= this -> x;
    y -= this -> y;

    return (x >= 0 && x <= this -> width) && (y >= 0 && y <= this -> height);
}

void TextField::setHidden(bool hidden)
{
    this -> hidden = hidden;
}

bool TextField::isHidden()
{
    return this -> hidden;
}

