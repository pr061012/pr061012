#include "Texture.h"

#include "../../../common/Log/Log.h"

Texture::Texture(const char* path, uint flags)
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

    this -> alpha   = flags & SOIL_FLAG_MULTIPLY_ALPHA;
    this -> repeats = flags & SOIL_FLAG_TEXTURE_REPEATS;

    if(this -> repeats)
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

        this -> scale = 1.0;
    }
    else
    {
        this -> setTextureDimensions(0.0, 0.0, 1.0, 1.0);
    }

}

Texture::~Texture()
{
    glDeleteTextures(1, &this -> texture);
}

void Texture::setTextureDimensions(double tex_x, double tex_y, double tex_w, double tex_h)
{
    this -> tex_x = tex_x;
    this -> tex_y = tex_y;
    this -> tex_w = tex_w;
    this -> tex_h = tex_h;
}

void Texture::setScale(double scale)
{
    this -> scale = scale;
}

double Texture::getScale()
{
    return this -> scale;
}

void Texture::render(double x, double y, double width, double height,
                         double x_offset, double y_offset) const
{
    // In case some texture is bound already, save it to rebind later.
    GLint boundTexture = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &boundTexture);

    double x1 = x + width;
    double y1 = y + height;

    double t_x;
    double t_y;
    double t_x1;
    double t_y1;

    if(this -> repeats)
    {
        x  /= scale;
        y  /= scale;
        x1 /= scale;
        y1 /= scale;

        x_offset /= scale;
        y_offset /= scale;

        t_x  = x  + x_offset;
        t_y  = y  + y_offset;
        t_x1 = x1 + x_offset;
        t_y1 = y1 + y_offset;
    }
    else
    {
        t_x  = tex_x + x_offset;
        t_y  = tex_y + y_offset;
        t_x1 = t_x + tex_w;
        t_y1 = t_y + tex_h;
    }

    glBindTexture(GL_TEXTURE_2D, this -> texture);

    glEnable(GL_TEXTURE_2D);
    if(this -> alpha)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }
    glBegin(GL_POLYGON);
        if(this -> repeats)
        {
            double z = 1.0 - 1.0/scale;

            glTexCoord2f(t_x , t_y ); glVertex3f(x , y , z);
            glTexCoord2f(t_x1, t_y ); glVertex3f(x1, y , z);
            glTexCoord2f(t_x1, t_y1); glVertex3f(x1, y1, z);
            glTexCoord2f(t_x , t_y1); glVertex3f(x , y1, z);
        }
        else
        {
            glTexCoord2f(t_x , t_y ); glVertex2f(x , y );
            glTexCoord2f(t_x1, t_y ); glVertex2f(x1, y );
            glTexCoord2f(t_x1, t_y1); glVertex2f(x1, y1);
            glTexCoord2f(t_x , t_y1); glVertex2f(x , y1);
        }
    glEnd();
    if(this -> alpha)
    {
        glDisable(GL_BLEND);
    }

    glDisable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, boundTexture);
}
