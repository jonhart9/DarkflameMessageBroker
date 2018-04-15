#pragma once

#include <functional>
#include <queue>
#include <unordered_map>

#include "message/IMessage.hpp"
#include "message/Message.hpp"
#include "message/MessageCallbackWrapper.hpp"
#include "IMessageBroker.hpp"

/**
 * A class to handle the brokering of event messages.
 */
template <typename MessageType>
class MessageBroker : public IMessageBroker {

    /** A shorthand for the callback function that we will use. */
    using message_callback = std::function<void(const MessageType&)>;

public:

    /**
     * The constructor.
     */
    MessageBroker() : subscriber_unique_id_(0) { }

    /**
     * Broadcast a message to all connected subscribers.
     *
     * @param message The message to broadcast
     */
    void broadcast(const MessageType& message) {

        // Store the broadcast for later, when the event loop is running
        message_queue_.push(message);
    }

    /**
     * Subscribes an object to an event type.
     *
     * @param messageCallback The callback function to be run. Has an argument of `const MessageType&`
     * @return The unique ID of this subscribed function
     */
    size_t subscribe(message_callback messageCallback) {

        // First, generate a new unique ID
        size_t uniqueID = subscriber_unique_id_++;

        // Now, store the message callback in the subscribers
        subscribers_.insert(std::make_pair(uniqueID, messageCallback));

        // Return the unique ID
        return uniqueID;
    }

    /**
     * Updates the broker by popping all current messages and emitting them
     * to their respective observers / subscribers.
     */
    void update() override {

        // Copy the updates so we don't have a recursion-like event
        // block the entire queue
        auto updates = message_queue_;

        // Emit all current messages
        while (!updates.empty()) {

            // Emit the message
            MessageType& message = updates.front();
            emit(message);

            // Pop the message from the queue
            updates.pop();
        }

        // Clear the queue
        message_queue_ = {};
    }

private:

    /**
     * A function to emit and run a message for all subscribers.
     *
     * @tparam MessageType The message object type
     * @param message The message object reference
     */
    void emit(const MessageType& message) {

        // Get the event from the hash map
        Message<MessageType> messageWrapper(message);
        for (auto it = subscribers_.begin(); it != subscribers_.end(); ++it) {
            it->second(messageWrapper);
        }
    }

private:

    /** The queue to hold all event messages. */
    std::queue<MessageType> message_queue_;

    /** A map of all subscribers functions. */
    std::unordered_map<size_t, message_callback> subscribers_;

    /** Hold the unique subscriber ID. */
    size_t subscriber_unique_id_;
};

