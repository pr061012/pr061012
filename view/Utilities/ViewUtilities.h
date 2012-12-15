/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#ifndef VIEW_UTILITIES_H
#define VIEW_UTILITIES_H

#include <GL/gl.h>
#include <GL/glc.h>
#include <string>
#include <cmath>

#include "../dev_glfw.h"
#include "../../common/BasicDefines.h"

class ViewUtilities
{
public:
    static void renderText(double x, double y, float size, std::string msg,
                           double line_size = 0.0);

    static void glRectf_blend(float x1, float y1, float x2, float y2,
                              bool filled = true);

    /**
     * @brief Draw a circle at specified screen coordinates.
     */
    static void glCirclef_blend(float x, float y, float rad,
                                bool filled = true);
};

#endif // VIEW_UTILITIES_H
