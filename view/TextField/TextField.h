/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <string>
#include <GL/glc.h>

class TextField
{
    std::string content;
    double x;
    double y;
    double height;
    double width;

public:

    TextField(double x, double y, double width, double height, std::string content = "");

    ~TextField();

    std::string getText();

    void setText(std::string content);

    void render();

    bool hitTest(double x, double y);
};

#endif // TEXT_FIELD_H
