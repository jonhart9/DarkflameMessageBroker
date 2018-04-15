#pragma once

#include <cstdlib>

/**
 * An interface for messages to inherit from
 */
class IMessage {
public:

    /**
     * The destructor.
     */
    virtual ~IMessage() { }

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