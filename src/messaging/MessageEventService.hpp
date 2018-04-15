#pragma once

#include <cstdio>
#include <unordered_map>

#include "MessageBroker.hpp"

/**
 * A class with minimal state responsible for subscribing message
 * subscriptions with their corresponding brokers and keeping
 * those brokers updated.
 */
class MessageEventService {

    /** A shorthand for the message callback. */
    template <typename MessageType>
    using message_callback = std::function<void(const MessageType&)>;

public:

    template <typename MessageType>
    void broadcast(const MessageType& message) {

        // First, make sure the broker exists
        size_t typeID = MessageBroker<MessageType>::getUniqueType();

        auto iterator = message_brokers.find(typeID);
        if (iterator == message_brokers.end()) return;

        // Broadcast the message to the broker
        dynamic_cast<MessageBroker<MessageType>*>(iterator->second)->broadcast(message);
    }

    /**
     * Subscribes a callback to a message event.
     *
     * @tparam MessageType The message type
     * @param callback The callback message
     * @return The subscriber ID
     */
    template <typename MessageType>
    size_t subscribe(message_callback<MessageType> callback) {

        // First, find the correct message broker based off the message type
        size_t typeID = MessageBroker<MessageType>::getUniqueType();

        // Make sure the message broker exists
        auto iterator = message_brokers.find(typeID);
        if (iterator == message_brokers.end()) {
            auto inserted = message_brokers.insert(std::make_pair(typeID, new MessageBroker<MessageType>()));
            if (!inserted.second) return 0;

            // Set the iterator to the inserted value.
            iterator = inserted.first;
        }

        // Now add the callback
        MessageBroker<MessageType> * broker = dynamic_cast<MessageBroker<MessageType>*>(iterator->second);
        if (broker == nullptr) return 0;

        return broker->subscribe(callback);
    }

    /**
     * Unsubscribes a subscriber from a message type.
     *
     * @tparam MessageType The message type
     * @param subscriberID The subscriber ID
     * @return Whether or not we unsubscribed.
     */
    template <typename MessageType>
    bool unsubscribe(size_t subscriberID) {

        // First, determine if the subscriber type has a broker
        size_t typeID = MessageBroker<MessageType>::getUniqueType();

        auto iterator = message_brokers.find(typeID);
        if (iterator == message_brokers.end()) {
            return false;
        }

        // If the type exists, just try to delete it from the broker
        MessageBroker<MessageType> * broker = dynamic_cast<MessageBroker<MessageType>*>(iterator->second);
        if (broker == nullptr) return false;

        // Return whether or not we unsubscribed
        return broker->unsubscribe(subscriberID);
    }

    /**
     * Updates the brokers.
     */
    void update() {

        // Update the brokers
        for (auto iterator = message_brokers.begin(); iterator != message_brokers.end(); ++iterator) {
            iterator->second->update();
        }
    }

private:

    /** The message brokers. */
    std::unordered_map<size_t, IMessageBroker*> message_brokers;
};