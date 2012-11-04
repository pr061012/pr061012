/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef RESOURCE_H
#define RESOURCE_H

#include "../Object.h"
#include "../Tool/Tool.h"

/**
 * @class Resource
 * @brief This class contains information about mineable or pickable resource.
 */
class Resource : public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    Resource(ResourceType type, unsigned int res_amount = 0);

    /**
     * @brief Destructor.
     */
    ~Resource();

    //**************************************************************************
    // CHANGING PROGRESS.
    //**************************************************************************

    /**
     * @brief Increment progress of mining by one.
     */
    void incrementProgress();

    //**************************************************************************
    // CHANGING AMOUNT.
    //**************************************************************************

    /**
     * @brief Decreases amount of resource.
     * @param delta amount of resource to decrease
     */
    void decreaseAmount(unsigned int delta);

    /**
     * @brief  Gets amount of resource.
     * @return amount of resource
     */
    unsigned int getAmount() const;

    //**************************************************************************
    // RESOURCE'S LIFE.
    //**************************************************************************

    /**
     * @brief  Gets array with pending actions.
     * @return array with pending actions
     */
    std::vector <Action> * getActions();

    //**************************************************************************
    // RESOURCE TYPE.
    //**************************************************************************

    /**
     * @brief  Gets the value of subtype.
     * @return the value of subtype
     */
    ResourceType getSubtype() const;

    //**************************************************************************
    // MINING.
    //**************************************************************************

    /**
     * @brief  Get the value of progress.
     * @return the value of progress
     */
    unsigned int getProgress() const;

    /**
     * @brief  Get the value of difficulty.
     * @return the value of difficulty
     */
    unsigned int getDifficulty() const;

    /**
     * @brief  Returns true if resource is mineable.
     * @return is mineable or not
     */
    bool isMineable() const;

private:
    /// Type of resource
    const ResourceType subtype;

    /// @brief Resource gathering process (Wood can't be hacked by one hit.
    ///        Humanoid needs several hits to do that.)
    unsigned int progress;
    /// Amount of steps to gather this resource.
    unsigned int difficulty;

    /// Amount of resource.
    unsigned int amount;
    /// Amount of resources received on each mining.
    unsigned int amount_per_drop;

    /// @brief Resource regeneration amount (amount of resource we regenerate on
    ///        each regeneration).
    unsigned int reg_amount;
    /// Amount of steps to regeneration.
    unsigned int steps_to_reg;

    /// @brief Resource maybe mineable (trees, ore, stone) or not. Look for
    ///        ResourceType enum for details.
    bool mineable;
};

#endif // RESOURCE_H
