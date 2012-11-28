/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "Message.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR
//******************************************************************************

Message::Message(const MessageType type, const Object* sender) :
    type(type),
    sender(sender)
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

const Object* Message::getSender() const
{
    return this -> sender;
}
