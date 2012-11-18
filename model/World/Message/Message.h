/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
#include <map>

class Object;
class Message;

#include "../Object/Object.h"
#include "../../../common/BasicTypes.h"

/**
 * @brief Messages are mechanism for communication between objects.
 */
class Message
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR
    //**************************************************************************

    /**
     * @brief Constructor.
     * @param type  message's type
     */
    Message(const MessageType type, const Object* sender);

    /**
     * @brief Destructor,
     */
    ~Message();

    //**************************************************************************
    // ACCESSING MESSAGE TYPE AND SENDER.
    //**************************************************************************

    /**
     * @brief  Gets type of message.
     * @return type of message
     */
    MessageType getType() const;

    /**
     * @brief  Gets message's sender.
     * @return message's sender
     */
    const Object* getSender() const;

private:
    /// Message type.
    const MessageType type;

    /// Message's sender.
    const Object* sender;
};

#endif // MESSAGE_H
