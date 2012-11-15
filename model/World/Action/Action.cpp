/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "Action.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR
//******************************************************************************

Action::Action(const ActionType type, Object * actor) :
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

ActionState Action::getState() const
{
    return this -> state;
}

bool Action::isPending() const
{
    return (this -> state == PENDING);
}

bool Action::isFailed() const
{
    return (this -> state == FAILED);
}

bool Action::isSucceeded() const
{
    return (this -> state == SUCCEEDED);
}

bool Action::isSucceededWithErrors() const
{
    return (this -> state == SUCCEEDED_WITH_ERRORS);
}

//**************************************************************************
// STATE'S CHANGERS.
//**************************************************************************

void Action::markAsPending()
{
    this -> state = PENDING;
}

void Action::markAsFailed()
{
    this -> state = FAILED;
}

void Action::markAsSucceeded()
{
    this -> state = SUCCEEDED;
}

void Action::markAsSucceededWithErrors()
{
    this -> state = SUCCEEDED_WITH_ERRORS;
}

//******************************************************************************
// ACCESSING PARAMS/PARTICIPANTS.
//******************************************************************************

void Action::addParticipant(Object* obj)
{
    this -> participants.push_back(obj);
}

std::vector <Object*> Action::getParticipants()
{
    return this -> participants;
}

Object* Action::getActor()
{
    return this -> actor;
}

ActionType Action::getType() const
{
    return this -> type;
}

ActionError Action::getError() const
{
    return this -> error;
}

void Action::setError(ActionError error)
{
    this -> error = error;
}
