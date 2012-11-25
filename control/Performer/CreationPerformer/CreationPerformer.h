/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef CREATION_PERFORMER_H
#define CREATION_PERFORMER_H

#include "../../../model/World/World.h"
#include "../Performer.h"
#include "../../../model/World/ObjectFactory/ObjectFactory.h"
#include "../../../model/World/Indexator/Indexator.h"
#include "../../../model/World/Object/Object.h"
#include "../../../common/ParamArray/ParamArray.h"

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
    CreationPerformer(World* world, ObjectHeap * visible, ObjectHeap * hidden);

    /**
     * @brief Destructor
     */
    virtual ~CreationPerformer();

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
    // HELPER FUNCTIONS
    //**************************************************************************

    /**
     * @brief Check coordinate
     * @param shape
     * @return possibility creation object with coordinate
     */
    bool checkCoord(Object *new_obj);

    Object* createBuilding(Action& action, ParamArray& param);

    Object* createCreature(Action& action, ParamArray& param);

    Object* createResource(Action& action, ParamArray& param);

    Object* createTool(Action& action, ParamArray &param);

    /// Buffer for visible objects
    ObjectHeap * visible;

    /// Buffer for hidden objects
    ObjectHeap * hidden;
};

#endif
