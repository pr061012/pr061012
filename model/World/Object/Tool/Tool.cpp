/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Tool.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Tool::Tool(ToolType type, ResourceType material) :
    Object(TOOL),
    subtype(type),
    material(material)
{
    // TODO Initialize max_strength and strength.
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
