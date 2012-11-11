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
    glDeleteTextures( 3, texture_buf ); // Clearing textures created
}

void ViewWorld::loadTextures()
{
    texture_buf[0] = SOIL_load_OGL_texture // Load an image file directly as a new OpenGL texture, using SOIL.
    (
        "res/grass.png",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS
    );

    texture_buf[1] = SOIL_load_OGL_texture
    (
        "res/tree.png",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA
    );

    texture_buf[2] = SOIL_load_OGL_texture
    (
        "res/cow.png",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA
    );
}



void ViewWorld::redraw()
{
    renderBackground();

    Object** objects = world->getViewObjectsInRange(x, y, VIEW_CAM_RADIUS);

    if(objects)
    {
        int i = 0;
        while( objects[i] != NULL )
        {
            renderObject( objects[i++] );
        }
    }
}

double ViewWorld::getX()
{
    return this->x;
}

double ViewWorld::getY()
{
    return this->y;
}

void ViewWorld::setX(double new_var)
{
    this->x = new_var;
}

void ViewWorld::setY(double new_var)
{
    this->y = new_var;
}

void ViewWorld::renderObject(Object* object)
{
    const Point &p = object->getCoords();

    double px = p.getX() - x;
    double py = p.getY() - y;

    px /= VIEW_CAM_RADIUS;
    py /= VIEW_CAM_RADIUS;
    px *= VIEW_CAM_SCALE;
    py *= VIEW_CAM_SCALE;

    // TODO: Redo image coordinates to be taken from (file?)
    float x0;
    float y0;
    float x1;
    float y1;

    float x_sz;
    float y_sz;

    if(object->getType() == RESOURCE)
    {
        x0 = 126.0/640;
        y0 = 1.0 - 110.0/480;
        x1 = 196.0/640;
        y1 = 1.0;

        x_sz = 0.33;
        y_sz = 0.5;

        glBindTexture(GL_TEXTURE_2D, texture_buf[1]);
    }
    if(object->getType() == CREATURE)
    {
        x0 = 0.0;
        y0 = 0.0;
        x1 = 1.0;
        y1 = 1.0;

        x_sz = 0.58;
        y_sz = 0.4;

        glBindTexture(GL_TEXTURE_2D, texture_buf[2]);
    }

    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBegin(GL_POLYGON);
        glTexCoord2f(x0, y0); glVertex2f(px-x_sz, py-y_sz);
        glTexCoord2f(x1, y0); glVertex2f(px+x_sz, py-y_sz);
        glTexCoord2f(x1, y1); glVertex2f(px+x_sz, py+y_sz);
        glTexCoord2f(x0, y1); glVertex2f(px-x_sz, py+y_sz);
    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void ViewWorld::renderBackground()
{
    double px = x/VIEW_CAM_RADIUS*VIEW_CAM_SCALE;
    double py = y/VIEW_CAM_RADIUS*VIEW_CAM_SCALE;

    glBindTexture(GL_TEXTURE_2D, texture_buf[0]);

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_POLYGON);
        glTexCoord2f(0.0  + px, 0.0  + py); glVertex2f(-8.0f, -8.0f);
        glTexCoord2f(16.0 + px, 0.0  + py); glVertex2f( 8.0f, -8.0f);
        glTexCoord2f(16.0 + px, 16.0 + py); glVertex2f( 8.0f,  8.0f);
        glTexCoord2f(0.0  + px, 16.0 + py); glVertex2f(-8.0f,  8.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f);
}
