/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <iostream>

#include "Tool.h"
#include "../../../../common/BasicDefines.h"
#include "../../../../common/Log/Log.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Tool::Tool(ToolType type, ResourceType material, uint max_strength) :
    Object(TOOL),
    subtype(type),
    material(material)
{
    // Initialising shape.
    this -> setShapeSize(SZ_TOOL_DIAM);
    this -> setShapeType(SHP_TOOL);

    // Trying to create Tool from non-mine resource.
    if
    (
        material != STONE &&
        material != BRONZE &&
        material != IRON &&
        material != SILVER &&
        material != GOLD
    )
    {
        Log::ERROR("Tried to create tool with material different from mine resource. Maybe it's  Controller error.");

        this -> max_strength     = 0;
        this -> current_strength = 0;
        return;
    }

    // Param max_strength is given, ignoring pre-defined values.
    if(max_strength != 0)
    {
        this -> max_strength     = max_strength;
        this -> current_strength = max_strength;
        return;
    }

    // Param max_strength isn't specified, using pre-defined instead.
    switch(material)
    {
        case STONE:  this -> max_strength = TOOL_STONE_STRENGTH;  break;
        case BRONZE: this -> max_strength = TOOL_BRONZE_STRENGTH; break;
        case IRON:   this -> max_strength = TOOL_IRON_STRENGTH;   break;
        case SILVER: this -> max_strength = TOOL_SILVER_STRENGTH; break;
        case GOLD:   this -> max_strength = TOOL_GOLD_STRENGTH;   break;
        default: break;
    }
    this -> current_strength = this -> max_strength;
}

Tool::~Tool()
{
}

//******************************************************************************
// INHERETED THINGS.
//******************************************************************************

std::vector <Action> * Tool::getActions()
{
    // Tool doens't have any actions.
    this -> actions.clear();

    return &(this -> actions);
}

void Tool::receiveMessage(Message message)
{
}

uint Tool::getHealthPoints() const
{
    return this -> current_strength;
}

uint Tool::getMaxHealthPoints() const
{
    return this -> max_strength;
}

std::string Tool::getTypeName() const
{
    return "tool";
}

//******************************************************************************
// STRENGTH.
//******************************************************************************

uint Tool::getStrength() const
{
    return this -> current_strength;
}

uint Tool::getMaxStrength() const
{
    return this -> max_strength;
}

void Tool::decreaseStrength(uint delta)
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

void Tool::increaseStrength(uint delta)
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

void Tool::damage(uint delta)
{
    this -> decreaseStrength(delta);
}

void Tool::heal(uint delta)
{
    this -> increaseStrength(delta);
}

//******************************************************************************
// TYPE ACCESSORS.
//******************************************************************************

ToolType Tool::getSubtype() const
{
    return this -> subtype;
}

ResourceType Tool::getMaterial() const
{
    return this -> material;
}
