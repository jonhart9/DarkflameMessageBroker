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
    virtual ~IMessage() = 0;

protected:

    /**
     * Returns a static integer value per object type to uniquely identify it.
     *
     * @return The unique type identifying the message
     */
    static size_t getUniqueType();

private:

    /** The unique type associated with this message. */
    static size_t uniqueType;
};