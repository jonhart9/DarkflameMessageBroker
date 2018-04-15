#pragma once

#include <cstdio>
#include <functional>

/**
 * The base message broker class.
 */
class IMessageBroker {
public:

    /**
     * Updates the message broker by releasing all queued
     * messages.
     */
    virtual void update() = 0;

protected:

    /**
     * Returns a static integer value per object type to uniquely identify it.
     *
     * @return The unique type identifying the message
     */
    static size_t getUniqueType() {
        static size_t uniqueType = 0;
        return uniqueType++;
    }
};