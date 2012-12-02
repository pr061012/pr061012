/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_TEXTURE_H
#define VIEW_TEXTURE_H

#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <string>

class ViewTexture
{
    /// Pointer to loaded texture data
    GLuint texture;

public:

    /**
     * @brief Constructor
     * @param path path to the texture file to be loaded
     */
    ViewTexture(const std::string path, uint flags);

    /**
     * @brief Destructor
     */
    ~ViewTexture();



};

#endif // VIEW_TEXTURE_H
