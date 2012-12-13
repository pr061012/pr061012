#include <vector>

#include "ViewWorld.h"


#include "../../common/Log/Log.h"

/// Max x and y of screen coordinates
#define VIEW_CAM_SIZE              8.0

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

ViewWorld::ViewWorld(const IWorld& w, const int& width, const int& height,
                     TextureManager* texture_manager) :
    world(w),
    texture_manager(texture_manager)
{
    this -> x = 50.0;
    this -> y = 50.0;

    this -> frame = 0;

    this -> width = width;
    this -> height = height;
    this -> cam_radius = (double) VIEW_CAM_RADIUS;

    this -> is_selected = false;

    this -> step = 0;

    this -> paused = false;
}

ViewWorld::~ViewWorld()
{
}

void ViewWorld::redraw()
{
    if(!this -> paused)
    {
        this -> step++;
    }
    if(this -> step > 30)
    {
        this -> step = 0;
    }

    std::vector<const Object*> objects = world.getViewObjectsInArea(x, y, getCamRad()*2);

    this -> renderBackground();

    rendered_objects.clear();

    for(uint i = 0; i < objects.size(); i++)
    {
        if(!objects.at(i)->isDestroyed())
        {
            rendered_objects.push_back(objects[i]);
            this -> renderObject(objects[i]);
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
    if(rad < 2.0) rad = 2.0;

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

void ViewWorld::setPaused(bool new_var)
{
    this -> paused = new_var;
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
        {
            const Resource* res = static_cast<const Resource*>(obj);
            switch(res -> getSubtype())
            {
                case BERRIES:
                    ret = texture_manager -> getTexture("Berry bush");
                    break;
                case WATER:
                    ret = texture_manager -> getTexture("Water");
                    break;
                case GRASS:
                    ret = NULL;
                    break;
                case MEAT:
                    ret = texture_manager -> getTexture("Meat");
                    break;
                default:
                    ret = texture_manager -> getTexture("Tree");
                    break;
            }

            break;
        }
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

                    if (aim)
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

                    if (act == SLEEP_AT_HOME || act == SLEEP_ON_THE_GROUND || act == RELAX_AT_HOME)
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

                    if (aim)
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
                                ret = texture_manager -> getTexture("Dragon", ang, nh -> getObjectID(), this -> step / 5);
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
        case WEATHER:
        {
//            ret = texture_manager -> getTexture("Cow");
            ret = NULL;
            break;
        }
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
            else if (res -> getSubtype() == WATER)
            {
                glColor4d(0.0, 1.0, 1.0, 0.4);
            }
            else if (res -> getSubtype() == BERRIES)
            {
                glColor4d(0.7, 0.0, 0.0, 0.4);
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

    const Texture* tex = this -> getObjectTexture(object);

    if(tex)
    {
        tex -> render(px, py, sz, sz);
    }
    else if(object -> getType() == WEATHER)
    {
//        const Weather* weat = static_cast<const Weather*>(object);

        glColor4d(0.0, 0.0, 0.0, 0.2);
        ViewUtilities::glCirclef_blend(px, py, sz/2);
        glColor3d(1.0, 1.0, 1.0);
    }
#endif

}

ViewWorld::Terrain ViewWorld::getTerrainType(double x, double y, double size)
{

    size *= 2.0;
    int greens = 0;

    //const Shape shp(Vector(x, y), SQUARE, size);

    for(uint i = 0; i < rendered_objects.size(); ++i)
    {
        // TODO: Consider adding a shape hitTest here.
        //       Right now it will make the algorithm laggy.

        const Object* obj = rendered_objects[i];
        double rx = abs(obj -> getCoords().getX() - x);
        double ry = abs(obj -> getCoords().getY() - y);

        if(rx < size && ry < size)
        {
            if(obj -> getType() == RESOURCE)
            {
                switch(static_cast<const Resource*>(obj) -> getSubtype())
                {
                    case BERRIES:
                    case TREE:
                        greens++;
                        break;
                    case GRASS:
                        greens += 2;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if(greens > 0)
    {
        return GRASS_TERRAIN;
    }
    else
    {
        return ROCK_TERRAIN;
    }
}

void ViewWorld::renderBackground()
{
#ifndef VIEW_DEBUG
    const double sz = SZ_HUM_DIAM * 2.0;
    const double sz_scr = worldToScreenDist(sz) + 0.06;

    double px = this -> getX() / sz;
    double py = this -> getY() / sz;

    px = -(px - floor(px)) * sz;
    py = -(py - floor(py)) * sz;

    const Texture* tex;


    double rad = getCamRad();
    int max = 2 * (rad / sz);
    Terrain** landscape = new Terrain*[2*max];
    double wx = this -> x - 2*rad - px;
    double wy;

    for(int i = 0; i < 2*max; ++i)
    {
        landscape[i] = new Terrain[2*max];

        wy = this -> y - 2*rad - py;
        for(int j = 0; j < 2*max; ++j)
        {
            landscape[i][j] = getTerrainType(wx, wy, sz);

            wy += sz;
        }
        wx += sz;
    }


    // Eight directions at neighbouring tiles.
    Terrain e, ne, n, nw, w, sw, s, se;

    int min = max/2 - 1;
    min = min > 1 ? min : 1;

    wx = this -> x - rad - px - sz;
    for(int i = min; i < max*3/2; ++i)
    {
        wy = this -> y - rad - py - sz;
        for(int j = min; j < max*3/2; ++j)
        {
//            w  = landscape[i-1][j];
//            s  = landscape[i]  [j-1];
            n  = landscape[i]  [j+1];
            e  = landscape[i+1][j];

//            sw = landscape[i-1][j-1];
            nw = landscape[i-1][j+1];
            se = landscape[i+1][j-1];
            ne = landscape[i+1][j+1];

            tex = texture_manager -> getTextureAt("Terrain", 1, 1);
            if(landscape[i][j] == GRASS_TERRAIN)
            {
                int tx = 3;
                int ty = 2;

                if(e == ROCK_TERRAIN && nw != ROCK_TERRAIN)
                {
                    tx = 0;
                    ty = 1;
                }
                else if(n == ROCK_TERRAIN && ne == GRASS_TERRAIN)
                {
                    tx = 2;
                    ty = 1;
                }
                else if(n == ROCK_TERRAIN && e == ROCK_TERRAIN)
                {
                    tx = 3;
                    ty = 0;
                }
                else if(n == ROCK_TERRAIN)
                {
                    tx = 1;
                    ty = 0;
                }
                else if(ne == ROCK_TERRAIN)
                {
                    tx = 0;
                    ty = 0;
                }
                else if(se == ROCK_TERRAIN && e == GRASS_TERRAIN)
                {
                    tx = 3;
                    ty = 2;
                }
                else if(se == ROCK_TERRAIN)
                {
                    tx = 0;
                    ty = 2;
                }

                tex = texture_manager -> getTextureAt("Terrain", tx, ty);
            }
            else if(landscape[i][j] == ROCK_TERRAIN)
            {
                int tx = 1;
                int ty = 1;

                if(e == GRASS_TERRAIN && ne == GRASS_TERRAIN)
                {
                    tx = 2;
                    ty = 1;
                }
                else if(se == GRASS_TERRAIN && e == GRASS_TERRAIN)
                {
                    tx = 4;
                    ty = 0;
                }
                else if(n == GRASS_TERRAIN && ne == GRASS_TERRAIN)
                {
                    tx = 1;
                    ty = 2;
                }
                else if(n == GRASS_TERRAIN)
                {
                    tx = 3;
                    ty = 1;
                }
                else if(ne == GRASS_TERRAIN)
                {
                    tx = 4;
                    ty = 1;
                }

                tex = texture_manager -> getTextureAt("Terrain", tx, ty);
            }

            tex -> render(worldToScreenX(wx)-0.03, worldToScreenY(wy)-0.03,
                          sz_scr, sz_scr);

            wy += sz;
        }
        wx += sz;
    }

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
