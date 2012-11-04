/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <iostream>

#include "Tool.h"
#include "../../../BasicDefines.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Tool::Tool(ToolType type, ResourceType material) :
    Object(TOOL),
    subtype(type),
    material(material)
{
    switch(material)
    {
        case STONE:  max_strength = TOOL_STONE_STRENGTH;  break;
        case BRONZE: max_strength = TOOL_BRONZE_STRENGTH; break;
        case IRON:   max_strength = TOOL_IRON_STRENGTH;   break;
        case SILVER: max_strength = TOOL_SILVER_STRENGTH; break;
        case GOLD:   max_strength = TOOL_GOLD_STRENGTH;   break;
        default:
            std::cerr << "[ERROR] Tool: tried to create tool with material " <<
                         "different from mine resource. Maybe it's " <<
                         "Controller error" << std::endl;
            max_strength = 0;
        break;
    }

    this -> current_strength = this -> max_strength;
}

Tool::~Tool()
{
}

//******************************************************************************
// TOOL ACTIONS.
//******************************************************************************

std::vector <Action> * Tool::getActions()
{
    // Tool doens't have any actions.
    this -> actions.clear();

    return &(this -> actions);
}

//******************************************************************************
// STRENGTH.
//******************************************************************************

unsigned int Tool::getStrength()
{
    return this -> current_strength;
}

unsigned int Tool::getMaxStrength()
{
    return this -> max_strength;
}

void Tool::decreaseStrength(unsigned int delta)
{
    if(this -> current_strength >= delta)
    {
        this -> current_strength -= delta;
    }
    else
    {
        this -> current_strength = 0;
    }
}

void Tool::increaseStrength(unsigned int delta)
{
    if(this -> current_strength + delta <= this -> max_strength)
    {
        this -> current_strength += delta;
    }
    else
    {
        this -> current_strength = this -> max_strength;
    }
}

//******************************************************************************
// TYPE ACCESSORS.
//******************************************************************************

ToolType Tool::getSubtype()
{
    return this -> subtype;
}

ResourceType Tool::getMaterial()
{
    return this -> material;
}
