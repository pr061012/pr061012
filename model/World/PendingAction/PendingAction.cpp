/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "PendingAction.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR
//******************************************************************************

PendingAction::PendingAction(const Object * actor, const PendingActionType type) :
    actor(actor),
    type(type)
{

}

PendingAction::~PendingAction()
{

}
