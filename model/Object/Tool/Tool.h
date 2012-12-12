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
    Tool(ToolType type, ResourceType material, uint max_strength = 0);

    /**
     * @brief Destructor.
     */
    virtual ~Tool();

    //**************************************************************************
    // INHERETED THINGS.
    //**************************************************************************

    std::string getTypeName() const;

    //**************************************************************************
    // HEALTH MANIPULATION.
    //**************************************************************************

    uint getHealthPoints() const;
    uint getMaxHealthPoints() const;

    uint damage(uint delta);
    uint heal(uint delta);

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
    uint current_strength;
    /// Tool's maximum possible strength.
    uint max_strength;
};

#endif // TOOL_H
