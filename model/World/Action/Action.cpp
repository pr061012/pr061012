/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Action.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR
//******************************************************************************

Action::Action(const ActionType type, const Object * actor) :
    type(type),
    actor(actor)
{

}

Action::~Action()
{

}

//******************************************************************************
// STATE'S CHECKERS
//******************************************************************************

ActionState Action::getState()
{
    return this -> state;
}

bool Action::isPending()
{
    return (this -> state == PENDING);
}

bool Action::isFailed()
{
    return (this -> state == FAILED);
}

bool Action::isSucceed()
{
    return (this -> state == SUCCEED);
}

//**************************************************************************
// STATE'S CHANGERS.
//**************************************************************************

void Action::markAsFailed()
{
    this -> state = FAILED;
}

void Action::markAsSucceed()
{
    this -> state = SUCCEED;
}

//******************************************************************************
// ACCESSING PARAMS/PARTICIPANTS.
//******************************************************************************

void Action::addParticipant(Object * obj)
{
    this -> participants.push_back(obj);
}

void Action::addParam(std::string param, int value)
{
    this -> params.addKey(param, value);
}

int Action::getParam(std::string param)
{
    return this -> params.getValue(param);
}
