#pragma once

#include "IMessage.hpp"

/**
 * A class that inherits from IMessage.
 */
template <typename MessageType>
class Message : public IMessage {
public:

    /**
     * Generates or returns the unique type for the object
     *
     * @return The unique message type
     */
    static size_t getUniqueType() {
        static size_t uniqueType = IMessage::getUniqueType();
        return uniqueType;
    }

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
    ~Message() override = default;

    /**
     * Gets a reference to the message type object stored in this message.
     *
     * @return The message type object reference.
     */
    const MessageType& getMessageType() const {
        return this->messageType_;
    }

private:

    /** A reference to the message type. */
    const MessageType& messageType_;
};