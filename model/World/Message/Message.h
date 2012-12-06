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
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     * @param type      message's type
     * @param reason    message's reason object
     */
    Message(const MessageType type, Object* reason);

    /**
     * @brief Destructor.
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
     * @brief  Gets message's reason.
     * @return message's reason
     */
    Object* getReason() const;

private:
    /// Message type.
    const MessageType type;

    /// Message's sender.
    Object* reason;
};

#endif // MESSAGE_H
