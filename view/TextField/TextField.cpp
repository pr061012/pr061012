#include "TextField.h"

#define VIEW_CAM_SIZE               8

TextField::TextField(double x, double y, double width, double height, std::string content)
{
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
    this -> content = content;
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
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(x, y, x+width, y+height);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);

//    int scr_width, scr_height;
//    glfwGetWindowSize(&scr_width,
//                      &scr_height);

    glcScale(height*VIEW_CAM_SIZE, height*VIEW_CAM_SIZE);
    glcRenderString( content.c_str() );
    glcScale(1.0/height/VIEW_CAM_SIZE, 1.0/height/VIEW_CAM_SIZE);
}

bool TextField::hitTest(double x, double y)
{
    x -= this -> x;
    y -= this -> y;

    return (x >= 0 && x <= this -> width) && (y >= 0 && y <= this -> height);
}

