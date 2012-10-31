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

//******************************************************************************
// STATE'S CHECKERS
//******************************************************************************

PendingActionStateType PendingAction::getState()
{
    return this -> state;
}

bool PendingAction::isPending()
{
    return (this -> state == PENDING);
}

bool PendingAction::isFailed()
{
    return (this -> state == FAILED);
}

bool PendingAction::isSucceed()
{
    return (this -> state == SUCCEED);
}

//******************************************************************************
// ACCESSING PARAMS.
//******************************************************************************

int PendingAction::getParam(std::string param)
{
    std::map <std::string, int> :: iterator iter = this -> params.find(param);

    if(iter == this -> params.end())
    {
        // TODO: Throw an exception.
    }

    return iter -> second;
}
