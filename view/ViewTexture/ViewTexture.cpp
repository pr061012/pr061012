#include "ViewTexture.h"

#include "../../common/Log/Log.h"

ViewTexture::ViewTexture(const std::string path, uint flags)
{

    this -> texture = SOIL_load_OGL_texture
    (
        path.c_str(),
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        flags
    );

    if (this -> texture == 0)
    {
        Log::ERROR("SOIL loading error:'" +
                   std::string(SOIL_last_result()) + "'.");
    }
}

ViewTexture::~ViewTexture()
{
    glDeleteTextures(1, &this -> texture);
}
