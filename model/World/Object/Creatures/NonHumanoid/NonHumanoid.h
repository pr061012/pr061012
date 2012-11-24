/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef NON_HUMANOID_H
#define NON_HUMANOID_H

#include "../Creature.h"

/**
 * @class NonHumanoid
 * @brief NonHumanoid is silly creature, has only few goals in its life: food
 *        and sleep.
 */
class NonHumanoid : public Creature
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Random constructor (creates NonHumanoid with really random
     *        attributes).
     * @param dmaker    non-humanoid's decision maker
     */
    NonHumanoid(const DecisionMaker & dmaker);

    /**
     * @brief Destructor
     */
    virtual ~NonHumanoid();

    //**************************************************************************
    // INHERETED THINGS.
    //**************************************************************************

    std::string getTypeName() const;
    std::string printObjectInfo() const;

    //**************************************************************************
    // NON-HUMANOID ACTIONS.
    //**************************************************************************

    std::vector <Action>* getActions();
    void receiveMessage(Message message);

    //**************************************************************************
    // NON-HUMANOID'S LOGICS.
    //**************************************************************************
private:
    //**************************************************************************
    // UPDATES
    //**************************************************************************
    /**
     * @brief Update age.
     */
    void updateAge();

    /**
     * @brief Update common attributes.
     */
    void updateCommonAttrs();

    /**
     * @brief Update need in descendants.
     */
    void updateNeedInDesc();
    //**************************************************************************
    // AUXILIARY FUNTIONS
    //**************************************************************************

    /**
     * @brief    Find grass around NHum
     * @return   the nearest grass
     */
    void findGrass();

    //**************************************************************************
    // TYPE
    //**************************************************************************
    NonHumanoidType subsubtype;
};

#endif // NON_HUMANOID_H
