/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>
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
    Resource(ResourceType type, uint res_amount = 0);

    /**
     * @brief Destructor.
     */
    virtual ~Resource();

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
    void decreaseAmount(uint delta);

    /**
     * @brief Increases amount of resource.
     * @param delta amount of resource to increase
     */
    void increaseAmount(uint delta);

    /**
     * @brief  Gets amount of resource.
     * @return amount of resource
     */
    uint getAmount() const;

    /**
     * @brief Returns is resource restorable.
     */
    bool isRestorable() const;

    /**
     * @brief Damages resource.
     * @param delta amount of damage
     */
    void damage(uint delta);

    /**
     * @brief ''Heals'' resource.
     * @param delta amount of healing points
     */
    void heal(uint delta);

    //**************************************************************************
    // RESOURCE'S LIFE.
    //**************************************************************************

    std::vector<Action>* getActions();
    void receiveMessage(Message message);

    std::string printObjectInfo() const;

    uint getHealthPoints() const;
    uint getMaxHealthPoints() const;

    std::string getTypeName() const;

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
    uint getProgress() const;

    /**
     * @brief Sets the value of progress.
     * @param progress  new value of progress
     */
    void setProgress(uint progress);

    /**
     * @brief  Get the value of difficulty.
     * @return the value of difficulty
     */
    uint getDifficulty() const;

    /**
     * @brief  Gets amount of steps to next resource regeneration.
     * @return value of steps to reg
     */
    uint getStepsToReg() const;

    /**
     * @brief  Gets resource's regeneration rate.
     * @return value of reg amount
     */
    uint getRegAmount() const;

    /**
     * @brief  Gets amount of resource, which will drop at each mining.
     * @return value of amount per drop
     */
    uint getAmountPerDrop() const;

    /**
     * @brief  Returns true if resource is mineable.
     * @return is mineable or not
     */
    bool isMineable() const;

    /**
     * @brief Makes resource mineable.
     */
    void makeMineable();

    /**
     * @brief Makes resource pickable.
     */
    void makePickable();

    /**
     * @brief Makes resource restorable.
     */
    void makeRestorable();

    /**
     * @brief Makes resource non-restorable.
     */
    void makeNonRestorable();

private:
    /// Type of resource
    const ResourceType subtype;

    /// @brief Resource gathering process (Wood can't be hacked by one hit.
    ///        Humanoid needs several hits to do that.)
    uint progress;
    /// Amount of steps to gather this resource.
    uint difficulty;

    /// Amount of resource.
    uint amount;
    /// Maximum possible amount.
    uint max_amount;
    /// Amount of resources received on each mining.
    uint amount_per_drop;

    /// @brief Resource regeneration amount (amount of resource we regenerate on
    ///        each regeneration).
    uint reg_amount;
    /// Amount of steps to regeneration.
    uint steps_to_reg;

    /// @brief Resource maybe mineable (trees, ore, stone) or not. Look for
    ///        ResourceType enum for details.
    bool mineable;

    /// Is resource restorable or not.
    bool restorable;
};

#endif // RESOURCE_H
