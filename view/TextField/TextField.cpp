#include "TextField.h"

#define VIEW_CAM_SIZE               8


TextField::TextField(double x, double y, double width, double height, 
#ifdef __glfw3_h__
    GLFWwindow window,
#endif
      std::string content) :
          content(content),
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
    this -> render_steps = 0;
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

void TextField::render(bool in_focus)
{
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);

    ViewUtilities::glRectf_blend(x, y, x + width, y + height);
    glColor3f(1.0f, 1.0f, 1.0f);

    int scr_width, scr_height;
    glfwGetWindowSize(&scr_width,
                      &scr_height);

    double scale = (double)scr_height / VIEW_CAM_SIZE * font_size;

    if(in_focus)
    {
        std::string str = this -> content;
        if(--render_steps < 30)
        {
            str += "|";
        }
        if(render_steps < 0)
        {
            render_steps = 60;
        }
        ViewUtilities::renderText(x, y + height / 4,
                                  scale, str);
    }
    else
    {
        ViewUtilities::renderText(x, y + height / 4,
                                  scale, content);
    }
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

