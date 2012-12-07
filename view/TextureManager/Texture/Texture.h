/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>

class Texture
{
    /// Pointer to loaded texture data
    GLuint texture;

    bool alpha;

    bool repeats;

    /// X and Y offsets of loaded texture
    double tex_x0;
    double tex_y0;

    double tex_x;
    double tex_y;

    /// Width and height dimensions of the selected texture
    double tex_w;
    double tex_h;

    double tex_max_w;
    double tex_max_h;

    /// Used only for repeating textures.
    double scale;

public:

    /**
     * @brief Constructor
     * @param path path to the texture file to be loaded
     */
    Texture(const char* path, uint flags, double x, double y, double width, double height);

    /**
     * @brief Destructor
     */
    ~Texture();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    double getX();
    double getY();
    double getWidth();
    double getHeight();

    void resetTextureDimensions();

    void setTextureDimensions(double tex_x, double tex_y, double tex_w, double tex_h);

    void setScale(double scale);
    double getScale();

    void render(double x, double y, double width, double height,
                double x_offset = 0.0, double y_offset = 0.0) const;
};

#endif // TEXTURE_H
