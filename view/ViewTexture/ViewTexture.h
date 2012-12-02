/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_TEXTURE_H
#define VIEW_TEXTURE_H

#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>

class ViewTexture
{
    /// Pointer to loaded texture data
    GLuint texture;

    bool alpha;

    bool repeats;

    /// Width and height dimensions of selected texture
    double tex_x;
    double tex_y;

    double tex_w;
    double tex_h;

    /// Used only for repeating textures.
    double scale;

public:

    /**
     * @brief Constructor
     * @param path path to the texture file to be loaded
     */
    ViewTexture(const char* path, uint flags);

    /**
     * @brief Destructor
     */
    ~ViewTexture();

    void setTextureDimensions(double tex_x, double tex_y, double tex_w, double tex_h);


    void render(double x, double y, double width, double height,
                double x_offset = 0.0, double y_offset = 0.0) const;
};

#endif // VIEW_TEXTURE_H
