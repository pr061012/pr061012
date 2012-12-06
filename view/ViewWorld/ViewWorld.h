/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VIEW_WORLD_H
#define VIEW_WORLD_H

#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

#include "../Utilities/ViewUtilities.h"
#include "../Texture/Texture.h"

#include "../../common/BasicTypes.h"
#include "../../common/BasicDefines.h"
#include "../../model/World/IWorld.h"
#include "../../model/World/Object/Object.h"
#include "../../model/World/Object/Creatures/Creature.h"
#include "../../model/World/Object/Creatures/Humanoid/Humanoid.h"
#include "../../model/World/Object/Resource/Resource.h"

class ViewWorld
{
    /// World that is rendered by this class
    const IWorld& world;

    /// Screen dimensions given by View
    int width;
    int height;

    double cam_radius;

    /// Flag to indicate if someone is selected.
    bool is_selected;

    /// Id of currently selected unit.
    uint selected_id;

    /// Objects which are displayed or used in some other
    /// way by View during the current frame. This is
    /// required to get information about units that are not
    /// rendered right now but selected by player.
    // std::vector<Object*> rendered_objects;

public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor
     * @param w world to render
     * @param width width of screen to render
     * @param height height of screen to render
     */
    ViewWorld(const IWorld& w, const int& width, const int& height,
              std::map<std::string, Texture*>& texture_buf, std::map<std::string, int>& texture_num);

    /**
     * @brief Destructor
     */
    ~ViewWorld();

private:
    //**************************************************************************
    // TEXTURE LOADING.
    //**************************************************************************

    /// map of loaded textures
    std::map<std::string, Texture*>& texture_buf;
    std::map<std::string, int>& texture_num;

    /**
     * @brief preload game textures in openGL
     */
    void loadTextures();

private:
    //**************************************************************************
    // DRAWING METHODS.
    //**************************************************************************

    /// X and Y coordinates of center of the game cam
    double x;
    double y;

    /// number of frames drawn
    int frame;

    /**
     * @brief draws specific object relative to current coordinates
     */
    void renderObject(const Object* object); // TODO: Object -> ViewObject

    /**
     * @brief render a grass background all over the window
     */
    void renderBackground();

public:
    /**
     * @brief redraw background and all objects in range of
     *        the game camera
     */
    void redraw();

    /**
     * @brief returns ViewObject situated at specific screen
     *        coordinates
     * @param x onscreen x coordinate 
     * @param y onscreen y coordinate 
     *
     */
    const std::vector<const Object*> getViewObjectAt(double x, double y);


    //**************************************************************************
    // COORDINATES TRANSFORMATION.
    //**************************************************************************

    double worldToScreenX(double world_x);
    double worldToScreenY(double world_y);

    double screenToWorldX(double screen_x);
    double screenToWorldY(double screen_y);

    double worldToScreenDist(double distance);


    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    const Texture* getTexture(std::string name, int index = 0);

    /**
     * @brief Returns current radius of game cam, in game length units.
     */
    double getCamRad();

    /**
     * @brief Changes current camera radius.
     * @param rad new radius
     */
    void setCamRad(double rad);

    /**
     * @brief Returns current coordinates of game camera center.
     */
    double getX();
    double getY();

    void setSelection(uint id);

    void clearSelection();

    const Object* getSelection();

    /**
     * @brief changes current width and height attributes
     */
    void setDimensions(const int& width, const int& height);

    /**
     * @brief set coordinates of center of the game cam
     */
    void setX(double new_var);
    void setY(double new_var);

    const Texture* getObjectTexture(const Object* obj);

};

#endif // VIEW_WORLD_H
