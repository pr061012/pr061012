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
class Tool : virtual public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    Tool(ToolType type);

    /**
     * @brief Destructor.
     */
    ~Tool();

    //**************************************************************************
    // USAGE.
    //**************************************************************************

	/**
     * @brief Use tool (decrease strength).
	 */
    void use();

    //**************************************************************************
    // TYPE ACCESSORS.
    //**************************************************************************

	/**
	 * Get the value of subtype
	 * @return the value of subtype
	 */
    ToolType getSubtype();

	/**
	 * Get the value of material
	 * @return the value of material
	 */
    ResourceType getMaterial();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

	/**
	 * Set the value of quality
	 * Качество изделия.
	 * @param new_var the new value of quality
	 */
    void setQuality(int new_var);

	/**
	 * Get the value of quality
	 * Качество изделия.
	 * @return the value of quality
	 */
    int getQuality();

private:
    /// Tool type.
    const ToolType subtype;

    /// Material of which tool is made.
    const ResourceType material;

    /// Tool quality.
    int quality;
};

#endif // TOOL_H
