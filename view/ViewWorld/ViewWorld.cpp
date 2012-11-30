#include <vector>

#include "ViewWorld.h"


#include "../../common/Log/Log.h"

/// Max x and y of screen coordinates
#define VIEW_CAM_SIZE               8

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

ViewWorld::ViewWorld(const IWorld& w, const int& width, const int& height) :
    world(w)
{
    loadTextures();

    for(int i = 0; i<2; ++i)
    {
        if( 0 == texture_buf[i] )
        {
            Log::ERROR("SOIL loading error:'" + std::string(SOIL_last_result()) + "'.");
        }
    }

    this -> x = 50.0;
    this -> y = 50.0;

    this -> frame = 0;

    this -> width = width;
    this -> height = height;
    this -> cam_radius = (double) VIEW_CAM_RADIUS;

    this -> selected_id = -1;
}

ViewWorld::~ViewWorld()
{
    glDeleteTextures( 3, texture_buf ); // Clearing textures that were previously created
}

void ViewWorld::loadTextures()
{
    this -> texture_buf[0] = SOIL_load_OGL_texture // Load an image file directly as a new OpenGL texture, using SOIL.
    (
        "res/rock.png",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS
    );

    glBindTexture(GL_TEXTURE_2D, texture_buf[0]);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    this -> texture_buf[1] = SOIL_load_OGL_texture
    (
        "res/tree.png",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA
    );

    this -> texture_buf[2] = SOIL_load_OGL_texture
    (
        "res/cow.png",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA
    );
}

void ViewWorld::redraw()
{
     this -> renderBackground();

    std::vector<const Object*> objects = world.getViewObjectsInArea(x, y, getCamRad()*2);

    for(uint i=0; i < objects.size(); i++)
    {
        if(!objects.at(i)->isDestroyed())
        {
            this -> renderObject(objects.at(i));
        }
    }
}


const std::vector<const Object*> ViewWorld::getViewObjectAt(double x, double y)
{
    return world.getViewObjectsInArea(x, y, VIEW_CURSOR_RAD);
}

double ViewWorld::worldToScreenX(double world_x)
{
    world_x -= this -> getX();
    return world_x / getCamRad() * VIEW_CAM_SIZE;
}

double ViewWorld::worldToScreenY(double world_y)
{
    world_y -= this -> getY();
    return world_y / getCamRad() * VIEW_CAM_SIZE;
}

double ViewWorld::screenToWorldX(double screen_x)
{
    return screen_x * getCamRad() / VIEW_CAM_SIZE + this -> getX();
}

double ViewWorld::screenToWorldY(double screen_y)
{
    return screen_y * getCamRad() / VIEW_CAM_SIZE + this -> getY();
}

double ViewWorld::worldToScreenDist(double distance)
{
    return distance / getCamRad() * VIEW_CAM_SIZE;
}

double ViewWorld::getCamRad()
{
    return this -> cam_radius;
}

void ViewWorld::setCamRad(double rad)
{
    this -> cam_radius = rad;
}

double ViewWorld::getX()
{
    return this -> x;
}

double ViewWorld::getY()
{
    return this -> y;
}

void ViewWorld::setSelection(uint id)
{
    this -> selected_id = id;
}

const Object* ViewWorld::getSelection()
{
    // TODO: I have to do it in more elegant way.

    if (this -> selected_id == -1)
    {
        return NULL;
    }

    return this -> world.getObjectByID(this -> selected_id);
}

void ViewWorld::setX(double new_var)
{
    new_var = new_var > getCamRad() ?
              new_var : getCamRad();
    new_var = new_var < world.getSize() - getCamRad() ?
              new_var : world.getSize() - getCamRad();
    this -> x = new_var;
}

void ViewWorld::setY(double new_var)
{
    const double y_max_rad = (double)getCamRad() * height / width;
    new_var = new_var > y_max_rad ?
              new_var : y_max_rad;
    new_var = new_var < world.getSize() - y_max_rad ?
              new_var : world.getSize() - y_max_rad;
    this -> y = new_var;
}

#ifdef VIEW_DEBUG
std::string act_repr[] = {"N", "S", "E", "B", "G", "R", "E", "C", "W", "RD", "ES", "REP", "DN"};
std::string hum_act_repr[] = {"H", "I_F", "F_F", "REL", "SL_H", "SL_G", "MINE", "B", "CH", "FI", "RUN"};
#endif

void ViewWorld::renderObject(const Object* object)
{
    const Vector &p = object -> getCoords();

    double px = this->worldToScreenX(p.getX());
    double py = this->worldToScreenY(p.getY());

#ifdef VIEW_DEBUG // In case of debug mode, circles are drawn instead of objects.
    switch(object -> getType())
    {
        case RESOURCE:
        {
            const Resource* res = dynamic_cast<const Resource*>(object);
            if(res -> getSubtype() == RES_BUILDING_MAT)
            {
                glColor4d(0.0, 1.0, 0.0, 0.4);
            }
            else
            {
                glColor4d(1.0, 0.0, 0.0, 0.4);
            }
        }
            break;
        case TOOL:
            glColor4d(0.0, 1.0, 1.0, 0.4);
            break;
        case BUILDING:
            glColor4d(0.0, 0.0, 1.0, 0.4);
            break;
        case WEATHER:
            glColor4d(0.0, 0.0, 0.0, 0.4);
            break;
        case CREATURE:
            double cx = worldToScreenX(object -> getCoords().getX());
            double cy = worldToScreenY(object -> getCoords().getY());
            double sz = worldToScreenDist(object -> getShape().getSize());

            std::string msg;
            if (dynamic_cast<const Creature*>(object) -> getSubtype() == HUMANOID)
            {
                CreatureAction action = (CreatureAction)dynamic_cast<const Humanoid*>(object) -> getCurrentDetailedAct();
                msg = hum_act_repr[action];
            }
            else
            {
                CreatureAction action = (CreatureAction)dynamic_cast<const Creature*>(object) -> getCurrentDecision();
                msg = act_repr[action];
            }
            ViewUtilities::renderText(cx-sz/2, cy-sz/2, sz*70.0, msg);
            glColor4d(1.0, 1.0, 1.0, 0.4);
            break;
    }

    double radius = this -> worldToScreenDist(object->getShape().getSize()/2);

    if (object -> getShape().getType() == CIRCLE)
    {
        ViewUtilities::glCirclef_blend(px, py, radius);

        if (object -> getObjectID() == selected_id)
        {
            glColor4d(1.0, 0.0, 1.0, 0.4);
            ViewUtilities::glCirclef_blend(px, py, radius, false);
        }
    }
    else
    {
        ViewUtilities::glRectf_blend(px-radius, py-radius, px+radius, py+radius);

        if (object -> getObjectID() == selected_id)
        {
            glColor4d(1.0, 0.0, 1.0, 0.4);
            ViewUtilities::glRectf_blend(px-radius, py-radius, px+radius, py+radius, false);
        }
    }

    glColor3d(1.0, 1.0, 1.0);
#else
    // TODO: Redo image coordinates to be taken from (file?)
    float x0;
    float y0;
    float x1;
    float y1;

    float x_sz;
    float y_sz;

    if (object -> getType() == RESOURCE)
    {
        x0 = 126.0/640;
        y0 = 1.0 - 110.0/480;
        x1 = 196.0/640;
        y1 = 1.0;

        x_sz = 0.33;
        y_sz = 0.5;

        glBindTexture(GL_TEXTURE_2D, texture_buf[1]);
    }
    if(object -> getType() == CREATURE)
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
#endif

}

void ViewWorld::renderBackground()
{
#ifndef VIEW_DEBUG
    double px = worldToScreenX( 0.0 );
    double py = worldToScreenY( 0.0 );

    py *= height/width;

    glBindTexture(GL_TEXTURE_2D, this -> texture_buf[0]);

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_POLYGON);
        glTexCoord2f(px       , py);
        glVertex2f(-VIEW_CAM_SIZE, -VIEW_CAM_SIZE);
        glTexCoord2f(px + 16.0, py);
        glVertex2f( VIEW_CAM_SIZE, -VIEW_CAM_SIZE);
        glTexCoord2f(px + 16.0, 16.0 + py);
        glVertex2f( VIEW_CAM_SIZE,  VIEW_CAM_SIZE);
        glTexCoord2f(0.0  + px, 16.0 + py);
        glVertex2f(-VIEW_CAM_SIZE,  VIEW_CAM_SIZE);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f);
#else
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
#endif
}

void ViewWorld::setDimensions(const int &width, const int &height)
{
    this -> width  = width;
    this -> height = height;
}
