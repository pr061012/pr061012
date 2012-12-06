/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#ifndef CREATION_PERFORMER_H
#define CREATION_PERFORMER_H

#include "../Performer.h"

#include "../../../common/ParamArray/ParamArray.h"

#include "../../../model/World/World.h"
#include "../../../model/World/Object/Object.h"

/**
 * @class CreationPerformer
 * @brief Performs a creation if it is possible
 */
class CreationPerformer : public Performer
{
public:
    
    //**************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //**************************************************************************

    /**
     * @brief Constructor
     * @param world world
     */
    CreationPerformer(World* world);

    /**
     * @brief Destructor
     */
    ~CreationPerformer();

    //**************************************************************************
    //  PERFORM
    //**************************************************************************
    
    /**
     * @brief Check if an object can create
     * @param action a request for creation
     */
    void perform(Action& action);

private:

    //**************************************************************************
    // AUXILIARY FUNCTIONS
    //**************************************************************************

    /**
     * @brief Check coordinate
     * @param shape
     * @return possibility creation object with coordinate
     */
    bool checkCoord(Object *new_obj);

    /**
     * @brief Auxiliary function for create building
     * @param action
     * @param param
     * @return object was created
     */
    Object* createBuilding(Action& action, ParamArray& param);

    /**
     * @brief Auxiliary function for create creature
     * @param action
     * @param param
     * @return object was created
     */
    Object* createCreature(Action& action, ParamArray& param);

    /**
     * @brief Auxiliary function for create tool
     * @param action
     * @param param
     * @return object was created
     */
    Object* createTool(Action& action, ParamArray& param);

    /**
     * @brief Auxiliary function for create weather
     * @param action
     * @param param
     * @return object was created
     */
    Object* createWeather(Action& action, ParamArray& param);

};

#endif
