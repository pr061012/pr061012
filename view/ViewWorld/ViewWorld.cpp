#include "ViewWorld.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

ViewWorld::ViewWorld(IWorld* w)
{
    loadTextures();

    for(int i = 0; i<2; ++i)
    {
        if( 0 == texture_buf[i] )
        {
            std::cerr<< "SOIL loading error:'" << SOIL_last_result() << "' \n";
        }
    }

    world = w;
    x = 50.0;
    y = 50.0;

    frame = 0;
}

ViewWorld::~ViewWorld()
{
    glDeleteTextures( 1, texture_buf ); // Clearing textures created
}

void ViewWorld::loadTextures()
{
    texture_buf[0] = SOIL_load_OGL_texture // Load an image file directly as a new OpenGL texture, using SOIL.
    (
        "../View/grass.png",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS
    );

    texture_buf[1] = SOIL_load_OGL_texture // Load an image file directly as a new OpenGL texture, using SOIL.
    (
        "../../res/tree.png",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA
    );
}



void ViewWorld::redraw()
{
    renderBackground();

    Object** objects = world->getViewObjectsInRange(x, y, CAM_RADIUS);

    if(objects)
    {
        int i = 0;
        while( objects[i] != NULL )
        {
            renderObject( objects[i++] );
        }
    }
}

void ViewWorld::setX(double new_var)
{
    x = new_var;
}

void ViewWorld::setY(double new_var)
{
    y = new_var;
}

void ViewWorld::renderObject(Object* object)
{
    const Point &p = object->getCoords();

    double px = p.getX() - x;
    double py = p.getY() - y;

    glColor3f(1.0, 1.0, 1.0);

    px /= CAM_RADIUS;
    py /= CAM_RADIUS;
    px *= 8;
    py *= 8;

    // TODO: Redo image coordinates to be taken from (file?)
    float x0 = 126.0/640;
    float y0 = 1.0 - 110.0/480;
    float x1 = 196.0/640;
    float y1 = 1.0;

    glBindTexture(GL_TEXTURE_2D, texture_buf[1]);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBegin(GL_POLYGON); // Drawing tree at specific place
        glTexCoord2f(x0, y0); glVertex2f(px-0.33, py-0.5);
        glTexCoord2f(x1, y0); glVertex2f(px+0.33, py-0.5);
        glTexCoord2f(x1, y1); glVertex2f(px+0.33, py+0.5);
        glTexCoord2f(x0, y1); glVertex2f(px-0.33, py+0.5);
    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D); // Fun part is done for this frame, 2D textures are drawn.
}

void ViewWorld::renderBackground()
{
    glBindTexture(GL_TEXTURE_2D, texture_buf[0]); // Choosing grass texture to render into the window

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the original
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glEnable(GL_TEXTURE_2D); // Entering texture drawing environment.

    glBegin(GL_POLYGON); // Texturing window frame with grass
        glTexCoord2f(0.0,   0.0); glVertex2f(-8.0f, -8.0f);
        glTexCoord2f(16.0,  0.0); glVertex2f( 8.0f, -8.0f);
        glTexCoord2f(16.0, 16.0); glVertex2f( 8.0f,  8.0f);
        glTexCoord2f(0.0,  16.0); glVertex2f(-8.0f,  8.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D); // Fun part is done for this frame, 2D textures are drawn.

    glColor3f(1.0f, 1.0f, 1.0f);
}
