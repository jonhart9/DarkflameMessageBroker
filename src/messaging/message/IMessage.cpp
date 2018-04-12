#include "IMessage.hpp"

/** Static Variables. */
size_t IMessage::uniqueType = 0;

/**
 * Increments the unique type identifier whenever a new object
 * type that inherits from IMessage is created.
 *
 * @return A new unique type
 */
size_t IMessage::getUniqueType() {
    return uniqueType++;
}