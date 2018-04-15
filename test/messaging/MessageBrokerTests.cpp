/**
 * A test suite for the MessageBroker class.
 */
#include "../../src/messaging/MessageBroker.hpp"

#include <gtest/gtest.h>

struct TestStruct1 { int i = 1; };
struct TestStruct2 { int i = 2; };

void testCallback1(const TestStruct1& testStruct1) { }
void testCallback2(const TestStruct2& testStruct2) { }
void testCallback3(const TestStruct1& testStruct1) { }

/**
 * Test to verify that the static unique IDs for object types
 * are set correctly.
 */
TEST(MessageBrokerTests, testMessageBrokerUniqueTypeID) {

    EXPECT_EQ(0, MessageBroker<TestStruct1>::getUniqueType());
    EXPECT_EQ(1, MessageBroker<TestStruct2>::getUniqueType());

    // Retest to make sure nothing changed
    EXPECT_EQ(0, MessageBroker<TestStruct1>::getUniqueType());
    EXPECT_EQ(1, MessageBroker<TestStruct2>::getUniqueType());
}

/**
 * Test to subscribe one type to an event manager and
 * verify that the subscriber ID is 0
 */
TEST(MessageBrokerTests, testMessageBrokerOneSubscriber) {

    MessageBroker<TestStruct1> messageBroker;
    size_t subscriberID = messageBroker.subscribe(&testCallback1);

    EXPECT_EQ(1, subscriberID);
}

/**
 * Test to verify that two subscribers from the same object
 * have separate IDs.
 */
TEST(MessageBrokerTests, testMessageBrokerTwoSubscribers) {

    MessageBroker<TestStruct1> messageBroker;
    size_t subscriberID_1 = messageBroker.subscribe(&testCallback1);
    size_t subscriberID_2 = messageBroker.subscribe(&testCallback3);

    EXPECT_EQ(1, subscriberID_1);
    EXPECT_EQ(2, subscriberID_2);
}

/**
 * Test to verify that removing a subscriber that exists
 * returns true.
 */
TEST(MessageBrokerTests, testMessageBrokerUnsubscribeExists) {

    MessageBroker<TestStruct1> messageBroker;
    size_t subscriberID = messageBroker.subscribe(&testCallback1);

    // Re-verify
    EXPECT_EQ(1, subscriberID);

    bool didUnsubscribe = messageBroker.unsubscribe(subscriberID);

    // Test to make sure
    EXPECT_EQ(true, didUnsubscribe);
}

/**
 * Test to verify that removing a subscriber that does not
 * exist returns false.
 */
TEST(MessageBrokerTests, testMessageBrokerUnsubscribeNotExists) {

    MessageBroker<TestStruct1> messageBroker;
    size_t subscriberID = messageBroker.subscribe(&testCallback1);

    // Re-verify
    EXPECT_EQ(1, subscriberID);

    bool didUnsubscribe = messageBroker.unsubscribe(2);

    // Verify
    EXPECT_EQ(false, didUnsubscribe);
}