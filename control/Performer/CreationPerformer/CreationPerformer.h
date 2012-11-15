/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef CREATION_PERFORMER_H
#define CREATION_PERFORMER_H

#include "../../../model/World/World.h"
#include "../Performer.h"
#include "../../../model/World/Indexator/Indexator.h"
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
     * @param indexator indexator
     */
    CreationPerformer(World* world);

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
    //  ATTRIBUTES
    //**************************************************************************

    /// The reference to worlds indexator
    Indexator* indexator;

    /// The reference to world
    World* world;

    ObjectFactory* factory;
    //**************************************************************************
    // HELPER FUNCTIONS
    //**************************************************************************

    /**
     * @brief check coordinate
     * @param x
     * @param y
     * @return possibility creation object with coordinate
     */
    bool checkCoord(uint x, uint y);

    Object* createBuilding(Action& action, ParamArray& param);

    Object* createCreature(Action& action, ParamArray& param);

    Object* createResource(Action& action, ParamArray& param);

    Object* createTool(Action& action, ParamArray &param);
};

#endif
