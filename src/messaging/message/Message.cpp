#include "Message.hpp"

/** Static Variables. */
size_t Message::uniqueType = IMessage::getUniqueType();

/**
 * Returns the unique type associated with this message.
 *
 * @return The unique type associated with this message
 */
size_t Message::getUniqueType() {
    return Message::uniqueType;
}