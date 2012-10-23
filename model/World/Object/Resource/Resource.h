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

    // TODO: Maybe constructor should receive some args?

    /**
     * @brief Constructor.
     */
    Resource();

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

    /**
     * @brief Make a resource's step in the world.
     *        (Maybe in this method we can regenerate resource.)
     */
    void step();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Set the value of progress.
     * @param new_var the new value of progress
     */
    void setProgress(int new_var);

    /**
     * @brief Get the value of progress.
     * @return the value of progress
     */
    int getProgress();

    /**
     * @brief Set the value of subtype.
     * @param new_var the new value of subtype
     */
    void setSubtype(ResourceType new_var);

    /**
     * @brief Get the value of subtype.
     * @return the value of subtype
     */
    ResourceType getSubtype();

    /**
     * @brief Set the value of regeneration_rate.
     * @param new_var the new value of regeneration_rate
     */
    void setRegenerationRate(int new_var);

    /**
     * @brief Get the value of regeneration_rate.
     * @return the value of regeneration_rate
     */
    int getRegenerationRate();

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
    void setDifficulty(int new_var);

    /**
     * @brief Get the value of difficulty.
     * @return the value of difficulty
     */
    int getDifficulty();

    /**
     * @brief Set the value of amount_per_gather.
     * @param new_var the new value of amount_per_gather
     */
    void setAmountPerGather(int new_var);

    /**
     * @brief Get the value of amount_per_gather.
     * @return the value of amount_per_gather
     */
    int getAmountPerGather();

private:
    /// @brief Resource gathering process (Wood can't be hacked by one hit.
    ///        Humanoid needs several hits to do that.)
    int progress;

    /// Type of resource
    ResourceType subtype;

    /// @brief Resource regeneration rate. (Either amount of steps to restore
    ///        1 resource unit or amount of steps to full regeneration or smth
    ///        else).
    int regeneration_rate;

    /// @brief Resource maybe gathered (trees, mountains, mines) or not (stones,
    ///        log, ore).
    bool gathered;

    /// Amount of steps to gather this resource.
    int difficulty;

    /// Amount of resources received on each gather step.
    int amount_per_gather;
};

#endif // RESOURCE_H
