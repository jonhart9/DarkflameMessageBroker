#pragma once

#include <functional>

/**
 * A base class for a message broker.
 */
class IMessageBroker {
public:

    /**
     * The destructor.
     */
    virtual ~IMessageBroker() { }

    /**
     * Updates the message queue by releasing queued events
     * to subscribers.
     */
    virtual void update();
};