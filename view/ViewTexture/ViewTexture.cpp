#include "ViewTexture.h"

#include "../../common/Log/Log.h"

ViewTexture::ViewTexture(const char* path, uint flags)
{

    this -> texture = SOIL_load_OGL_texture
    (
        path,
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        flags
    );

    if (this -> texture == 0)
    {
        Log::ERROR("SOIL loading error:'" +
                   std::string(SOIL_last_result()) + "'.");
    }

    this -> alpha = flags & SOIL_FLAG_MULTIPLY_ALPHA;

    if(flags & SOIL_FLAG_TEXTURE_REPEATS)
    {
        // In case some texture is bound already, save it to rebind later.
        GLint boundTexture = 0;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &boundTexture);

        glBindTexture(GL_TEXTURE_2D, this -> texture);
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        // Rebinding the texture that was bound beforehand.
        glBindTexture(GL_TEXTURE_2D, boundTexture);
    }
}

ViewTexture::~ViewTexture()
{
    glDeleteTextures(1, &this -> texture);
}

void ViewTexture::render(double x, double y, double width, double height,
                         double x_offset, double y_offset) const
{
    // In case some texture is bound already, save it to rebind later.
    GLint boundTexture = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &boundTexture);

    double x1 = x + width;
    double y1 = y + height;

    glBindTexture(GL_TEXTURE_2D, this -> texture);

    glEnable(GL_TEXTURE_2D);
    if(this -> alpha)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }
    glBegin(GL_POLYGON);
        glTexCoord2f(x  + x_offset, y  + y_offset); glVertex2f(x , y );
        glTexCoord2f(x1 + x_offset, y  + y_offset); glVertex2f(x1, y );
        glTexCoord2f(x1 + x_offset, y1 + y_offset); glVertex2f(x1, y1);
        glTexCoord2f(x  + x_offset, y1 + y_offset); glVertex2f(x , y1);
    glEnd();
    if(this -> alpha)
    {
        glDisable(GL_BLEND);
    }

    glDisable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, boundTexture);
}
