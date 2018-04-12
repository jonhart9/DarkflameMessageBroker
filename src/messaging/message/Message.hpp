#pragma once

#include "IMessage.hpp"

/**
 * A class that inherits from IMessage.
 */
template <typename MessageType>
class Message : public IMessage {
public:

    /**
     * Gets the unique message type.
     *
     * @return The unique message type
     */
    static size_t getUniqueType();

public:

    /**
     * The constructor.
     *
     * @param messageType The underlying message type
     */
    explicit Message(const MessageType& messageType) : messageType_(messageType) { }

    /**
     * The destructor.
     */
    explicit ~Message() override { }

    /**
     * Gets a reference to the message type object stored in this message.
     *
     * @return The message type object reference.
     */
    const MessageType& getMessageType() {
        return this->messageType_;
    }

private:

    /** The unique type. */
    static size_t uniqueType;

    /** A reference to the message type. */
    const MessageType& messageType_;
};