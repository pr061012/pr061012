#include <vector>

#include "ViewWorld.h"


#include "../../common/Log/Log.h"

/// Max x and y of screen coordinates
#define VIEW_CAM_SIZE               8

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

ViewWorld::ViewWorld(const IWorld& w, const int& width, const int& height,
                     TextureManager* texture_manager) :
    world(w),
    texture_manager(texture_manager)
{
    loadTextures();

    this -> x = 50.0;
    this -> y = 50.0;

    this -> frame = 0;

    this -> width = width;
    this -> height = height;
    this -> cam_radius = (double) VIEW_CAM_RADIUS;

    this -> is_selected = false;

    this -> step = 0;
}

ViewWorld::~ViewWorld()
{
}

void ViewWorld::loadTextures()
{
}

void ViewWorld::redraw()
{
    this -> step++;
    if(this -> step > 15)
    {
        this -> step = 0;
    }

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

    texture_manager -> getTexture("Rock") -> setScale(VIEW_CAM_RADIUS / rad);
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
    this -> is_selected = true;
}

void ViewWorld::clearSelection()
{
    this -> is_selected = false;
}

const Object* ViewWorld::getSelection()
{
    if (!this -> is_selected)
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
    const double y_max_rad = getCamRad() * height / width;
    new_var = new_var > y_max_rad ?
              new_var : y_max_rad;
    new_var = new_var < world.getSize() - y_max_rad ?
              new_var : world.getSize() - y_max_rad;
    this -> y = new_var;
}

const Texture* ViewWorld::getObjectTexture(const Object *obj)
{
    const Texture* ret = NULL;

    switch(obj -> getType())
    {
        case RESOURCE:
            ret = texture_manager -> getTexture("Tree");
            break;
        case CREATURE:
        {
            const Creature* cr = static_cast<const Creature*>(obj);

            switch(cr -> getSubtype())
            {
                case HUMANOID:
                {
                    const Humanoid* h = static_cast<const Humanoid*>(obj);

                    const Object* aim = h -> getAim();
                    double ang = M_PI*3/2;

                    if(aim)
                    {
                        double hx = h -> getCoords().getX();
                        double hy = h -> getCoords().getY();

                        double ax = aim -> getCoords().getX();
                        double ay = aim -> getCoords().getY();

                        ang = atan((hy-ay)/(hx-ax));
                        ang += M_PI/2;

                        if(ax < hx)
                        {
                            ang += M_PI;
                        }
                    }

                    uint act = h -> getCurrentDetailedAct();

                    if(act == SLEEP_AT_HOME || act == SLEEP_ON_THE_GROUND || act == RELAX_AT_HOME)
                    {
                        ret = texture_manager -> getTexture("Human", ang, h -> getObjectID(), 1);
                    }
                    else
                    {
                        ret = texture_manager -> getTexture("Human", ang, h -> getObjectID(), this -> step / 5);
                    }

                    break;
                }
                case NON_HUMANOID:
                {
                    const NonHumanoid* nh = static_cast<const NonHumanoid*>(obj);

                    const Object* aim = nh -> getAim();
                    double ang = M_PI*3/2;

                    if(aim)
                    {
                        double hx = nh -> getCoords().getX();
                        double hy = nh -> getCoords().getY();

                        double ax = aim -> getCoords().getX();
                        double ay = aim -> getCoords().getY();

                        ang = atan((hy-ay)/(hx-ax));
                        ang += M_PI/2;

                        if(ax < hx)
                        {
                            ang += M_PI;
                        }
                    }

                    uint act = nh -> getCurrentAction();

                    switch(nh -> getSubsubtype())
                    {
                        case COW:
                        case COW_DEMON:
                            ret = texture_manager -> getTexture("Cow");
                            break;
                        case DRAGON:
                        {
                            if(act == RELAX || act == SLEEP || act == DO_NOTHING)
                            {
                                ret = texture_manager -> getTexture("Dragon", ang, nh -> getObjectID(), 1);
                            }
                            else
                            {
                                ret = texture_manager -> getTexture("Dragon", ang, nh -> getObjectID(), this -> step / 5);
                            }

                            break;
                        }
                    }

                    break;
                }
            }
            break;
        }
        case BUILDING:
            ret = texture_manager -> getTexture("House");
            break;
        default:
            ret = texture_manager -> getTexture("Cow");
            break;
    }
    return ret;
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
            if(res -> getSubtype() == TREE)
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
                CreatureAction action = (CreatureAction)dynamic_cast<const Creature*>(object) -> getCurrentAction();
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

        if (is_selected && object -> getObjectID() == selected_id)
        {
            glColor4d(1.0, 0.0, 1.0, 0.4);
            ViewUtilities::glCirclef_blend(px, py, radius, false);
        }
    }
    else
    {
        ViewUtilities::glRectf_blend(px-radius, py-radius, px+radius, py+radius);

        if (is_selected && object -> getObjectID() == selected_id)
        {
            glColor4d(1.0, 0.0, 1.0, 0.4);
            ViewUtilities::glRectf_blend(px-radius, py-radius, px+radius, py+radius, false);
        }
    }

    glColor3d(1.0, 1.0, 1.0);
#else

    double sz = object -> getShape().getSize();
    sz  = worldToScreenDist(sz);
    px -= sz/2;
    py -= sz/2;

    this -> getObjectTexture(object) -> render(px, py, sz, sz);
#endif

}

void ViewWorld::renderBackground()
{
#ifndef VIEW_DEBUG
    double px = worldToScreenX( x - floor(x) );
    double py = worldToScreenY( y - floor(y) );


    texture_manager -> getTexture("Rock") -> render( -VIEW_CAM_SIZE,  -VIEW_CAM_SIZE,
                                         2*VIEW_CAM_SIZE, 2*VIEW_CAM_SIZE,
                                         -px, -py);

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
