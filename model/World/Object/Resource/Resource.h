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
class Resource : virtual public Object
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

    /**
     * @brief  Resource gathering. Should be spawned only by Tool.
     * @param  tool that spawned gathering
     * @return amount of gathered resource
     */
    unsigned int gather(Tool tool);

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Set the value of progress.
     * @param new_var the new value of progress
     */
    void setProgress(unsigned int new_var);

    /**
     * @brief Get the value of progress.
     * @return the value of progress
     */
    int getProgress();

    /**
     * @brief Set the value of regeneration_rate.
     * @param new_var the new value of regeneration_rate
     */
    void setRegenerationRate(unsigned int new_var);

    /**
     * @brief Get the value of regeneration_rate.
     * @return the value of regeneration_rate
     */
    unsigned int getRegenerationRate();

    /**
     * @brief Set the value of gathered.
     * @param new_var the new value of gathered
     */
    void setGathered(bool new_var);

    /**
     * @brief Get the value of gathered.
     * @return the value of gathered
     */
    bool getGathered();

    /**
     * @brief Set the value of difficulty.
     * @param new_var the new value of difficulty
     */
    void setDifficulty(unsigned int new_var);

    /**
     * @brief Get the value of difficulty.
     * @return the value of difficulty
     */
    unsigned int getDifficulty();

    /**
     * @brief Set the value of amount_per_gather.
     * @param new_var the new value of amount_per_gather
     */
    void setAmountPerGather(unsigned int new_var);

    /**
     * @brief Get the value of amount_per_gather.
     * @return the value of amount_per_gather
     */
    unsigned int getAmountPerGather();

private:
    /// @brief Resource gathering process (Wood can't be hacked by one hit.
    ///        Humanoid needs several hits to do that.)
    unsigned int progress;

    /// Amount of resource.
    unsigned int amount;

    /// Type of resource
    const ResourceType subtype;

    /// @brief Resource regeneration rate. (Either amount of steps to restore
    ///        1 resource unit or amount of steps to full regeneration or smth
    ///        else).
    unsigned int regeneration_rate;

    /// @brief Resource maybe gathered (trees, mountains, mines) or not (stones,
    ///        log, ore).
    bool gathered;

    /// Amount of steps to gather this resource.
    unsigned int difficulty;

    /// Amount of resources received on each gather step.
    unsigned int amount_per_gather;
};

#endif // RESOURCE_H
