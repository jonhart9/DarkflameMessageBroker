#pragma once

#include <cstdio>
#include <functional>
#include <unordered_map>

#include "IMessageBroker.hpp"

template <typename MessageType>
class MessageBroker : public IMessageBroker {

    /** A shorthand for the message callback. */
    using message_callback = std::function<void(const MessageType&)>;

public:

    /**
     * Generates or returns the unique type for the object
     *
     * @return The unique message type
     */
    static size_t getUniqueType() {
        static size_t uniqueType = IMessageBroker::getUniqueType();
        return uniqueType;
    }

public:

    /**
     * Subscribes a callback to a message.
     *
     * @param callback The message callback
     * @return The subscriber ID
     */
    size_t subscribe(message_callback callback) {

        // Save the message callback to the subscribers
        size_t subscriberID = subscriber_id++;
        subscribers.insert(std::make_pair(subscriberID, callback));

        return subscriberID;
    }

    /**
     * Unsubscribe an message event from the event manager.
     *
     * @param subscriberID The subscriber ID
     * @return Whether or not it was un-subscribed effectively.
     */
    bool unsubscribe(size_t subscriberID) {

        // First, figure out if the subscriber ID already exists
        auto iterator = subscribers.find(subscriberID);
        if (iterator == subscribers.end()) {
            return false;
        }

        // Now, remove the data from the array
        subscribers.erase(subscriberID);
        return true;
    }

    /**
     * Updates the data by releasing all queued
     * message events.
     */
    void update() override {
        // TODO: Implement...
    }

private:

    size_t subscriber_id = 1;

    /** A map of the subscribers with their IDs. */
    std::unordered_map<size_t, message_callback> subscribers;
};