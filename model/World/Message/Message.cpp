/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "Message.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR
//******************************************************************************

Message::Message(const MessageType type, Object* reason) :
    type(type),
    reason(reason)
{
}

Message::~Message()
{

}

//******************************************************************************
// ACCESSING MESSAGE TYPE AND SENDER.
//******************************************************************************

MessageType Message::getType() const
{
    return this -> type;
}

Object* Message::getReason() const
{
    return this -> reason;
}
