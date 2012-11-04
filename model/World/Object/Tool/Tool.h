/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef TOOL_H
#define TOOL_H

#include "../Object.h"

/**
 * @class Tool
 * @brief Tool class
 */
class Tool : public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    Tool(ToolType type, ResourceType material);

    /**
     * @brief Destructor.
     */
    ~Tool();

    //**************************************************************************
    // TOOL ACTIONS.
    //**************************************************************************

    /**
     * @brief  Gets actions.
     * @return vector with actions.
     */
    std::vector <Action> * getActions();

    //**************************************************************************
    // STRENGTH.
    //**************************************************************************

    /**
     * @brief  Gets current tool's strength.
     * @return the value of current strength
     */
    unsigned int getStrength() const;

    /**
     * @brief  Gets maximum possible tool's strength.
     * @return the value of maximum strength
     */
    unsigned int getMaxStrength() const;

    /**
     * @brief Decreases current tool's strength.
     * @param delta the value to subtract
     */
    void decreaseStrength(unsigned int delta);

    /**
     * @brief Increases current tool's strength.
     * @param delta the value to add
     */
    void increaseStrength(unsigned int delta);

    //**************************************************************************
    // TYPE ACCESSORS.
    //**************************************************************************

	/**
     * @brief  Gets tool's type.
     * @return tool's type
	 */
    ToolType getSubtype() const;

    /**
     * @brief  Gets tool's material.
     * @return tool's material
	 */
    ResourceType getMaterial() const;

private:
    /// Tool type.
    const ToolType subtype;

    /// Material of which tool is made.
    const ResourceType material;

    /// Tool's current strength.
    unsigned int current_strength;
    /// Tool's maximum possible strength.
    unsigned int max_strength;
};

#endif // TOOL_H
