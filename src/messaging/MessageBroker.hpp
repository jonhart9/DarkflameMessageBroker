#pragma once

#include <cstdio>
#include <functional>
#include <unordered_map>
#include <queue>

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
     * Broadcasts a message to the subscribers.
     *
     * @param message The message to be broadcast to subscribers
     */
    void broadcast(const MessageType& message) {

        // Add the message to the queue
        message_queue.push(message);
    }

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

        // First, get the size of the queue (so we don't have to copy it)
        // This makes sure any events broadcasts recursively are not called
        // immediately, so that we don't have an infinite loop
        size_t queueSize = message_queue.size();

        // Now, keep popping the queue
        for (; queueSize > 0; --queueSize) {

            // Get the message
            const MessageType& message = message_queue.front();
            emit(message);

            // Now remove the message
            message_queue.pop();
        }
    }

private:

    /**
     * Emits message to their corresponding subscribers.
     *
     * @param message The message to emit
     */
    void emit(const MessageType& message) {

        // Emit the message to all subscribers
        for (auto iterator = subscribers.begin(); iterator != subscribers.end(); ++iterator) {
            iterator->second(message);
        }
    }

private:

    /** The message queue. */
    std::queue<const MessageType> message_queue;

    /** The current subscriber ID for this broker. */
    size_t subscriber_id = 1;

    /** A map of the subscribers with their IDs. */
    std::unordered_map<size_t, message_callback> subscribers;
};