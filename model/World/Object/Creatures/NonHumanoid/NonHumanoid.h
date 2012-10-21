/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef NON_HUMANOID_H
#define NON_HUMANOID_H

#include "../Creature.h"

/**
 * @class NonHumanoid
 * @brief
 */
class NonHumanoid : virtual public Creature
{
public:
    /**
     * @brief Random constructor (creates NonHumanoid with really random
     *        attributes).
     * @param dmaker    non-humanoid's decision maker
     */
    Humanoid(const DecisionMaker & dmaker);

    /**
     * @brief Destructor
     */
    ~Humanoid();

    /**
     * @brief Makes a next step.
     */
    void step();
};

#endif // NON_HUMANOID_H
