#pragma once

#include <functional>
#include <queue>
#include <unordered_map>

#include "message/IMessage.hpp"
#include "message/Message.hpp"
#include "message/MessageCallbackWrapper.hpp"

/**
 * A class to handle the brokering of event messages.
 */
class MessageBroker {

    /** A shorthand for the callback function that we will use. */
    template <typename MessageType>
    using message_callback = std::function<void(const MessageType&)>;

public:

    // TODO: Implement...

    /**
     * The constructor.
     */
    MessageBroker() : subscriber_unique_id_(0) { }

    /**
     * Subscribes an object to an event type.
     *
     * @tparam MessageType The object type that we are subscribing to
     * @param messageCallback The callback function to be run. Has an argument of `const MessageType&`
     * @return The unique ID of this subscribed function
     */
    template <typename MessageType>
    size_t subscribe(message_callback<MessageType> messageCallback) {

        // First, generate a new unique ID
        size_t uniqueID = subscriber_unique_id_++;

        // First, make sure we have an unordered map for the map
        auto iterator = subscribers_.find(Message<MessageType>::getUniqueType());
        if (iterator == subscribers_.end()) {
            subscribers_.insert(std::make_pair(Message<MessageType>::getUniqueType(), std::unordered_map<size_t, message_callback<IMessage>>()));
        }

        // Now, store the message callback in the subscribers
        iterator = subscribers_.find(Message<MessageType>::getUniqueType());
        iterator->second.insert(std::make_pair(uniqueID, MessageCallbackWrapper<MessageType>(messageCallback)));

        // Return the unique ID
        return uniqueID;
    }


private:

    /** The queue to hold all event messages. */
    std::queue<IMessage> message_queue_;

    /** A map of all subscribers functions. */
    std::unordered_map<size_t, std::unordered_map<size_t, message_callback<IMessage>>> subscribers_;

    /** Hold the unique subscriber ID. */
    size_t subscriber_unique_id_;
};

