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
 * @brief Resource class contains information about one mineral deposit.
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
    Resource(const ResourceType type);

    /**
     * @brief Destructor.
     */
    ~Resource();

    //**************************************************************************
    // RESOURCE'S LIFE.
    //**************************************************************************

    /**
     * @brief Decreases amount of resource.
     * @param delta amount of resource to decrease
     */
    void decreaseAmount(unsigned int delta);

    /**
     * @brief  Gets array with pending actions.
     * @return array with pending actions
     */
    std::vector <Action> * getActions();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Get the value of progress.
     * @return the value of progress
     */
    unsigned int getProgress();

    /**
     * @brief  Gets the value of subtype.
     * @return the value of subtype
     */
    ResourceType getSubtype();

    /**
     * @brief Get the value of regeneration_rate.
     * @return the value of regeneration_rate
     */
    unsigned int getRegenerationRate();

    /**
     * @brief Get the value of gathered.
     * @return the value of gathered
     */
    bool getGathered();

    /**
     * @brief Get the value of difficulty.
     * @return the value of difficulty
     */
    unsigned int getDifficulty();

    /**
     * @brief Get the value of amount_per_gather.
     * @return the value of amount_per_gather
     */
    unsigned int getAmountPerGather();

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
    /// Amount of resources received on each gather step.
    unsigned int amount_per_gather;

    /// @brief Resource regeneration rate (amount of resource we regenerate on
    ///        each step).
    unsigned int regeneration_rate;

    /// @brief Resource maybe gathered (trees, mountains, mines) or not (stones,
    ///        log, ore).
    bool gathered;
};

#endif // RESOURCE_H
