/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Tool.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Tool::Tool():Object(TOOL)
{

}

Tool::~Tool()
{

}

//******************************************************************************
// USAGE.
//******************************************************************************

void Tool::use()
{

}

//******************************************************************************
// ACCESSORS.
//******************************************************************************

void Tool::setSubtype(ToolType new_var)
{
    this -> subtype = new_var;
}

ToolType Tool::getSubtype()
{
    return this -> subtype;
}

void Tool::setMaterial(ResourceType new_var)
{
    this -> material = new_var;
}

ResourceType Tool::getMaterial()
{
    return this -> material;
}

void Tool::setQuality(int new_var)
{
    this -> quality = new_var;
}

int Tool::getQuality()
{
    return this -> quality;
}
