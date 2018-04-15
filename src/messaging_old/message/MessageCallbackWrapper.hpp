#pragma once

#include <functional>

#include "IMessage.hpp"
#include "Message.hpp"

/**
 * A class to hold a message callback function in memory.
 *
 * @tparam MessageType The message object type
 */
template <typename MessageType>
class MessageCallbackWrapper {

    /** A shorthand for the message callback function. */
    using message_callback = std::function<void(const MessageType&)>;

public:

    /**
     * The constructor.
     *
     * @param messageCallback The message callback function
     */
    explicit MessageCallbackWrapper(message_callback messageCallback) : callback_(messageCallback) { }

    /**
     * The () operator to run the message callback function.
     *
     * @param message the message callback function
     */
    void operator() (const IMessage& message) {
        callback_(static_cast<const Message<MessageType>&>(message).getMessageType());
    }

private:

    /** The stored message callback. */
    message_callback callback_;
};