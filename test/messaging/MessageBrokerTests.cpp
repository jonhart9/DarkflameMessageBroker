/**
 * A test case file to verify the integrity of the {@link MessageBroker} class.
 */
#include <gtest/gtest.h>
#include <cstdio>

#include "../../src/messaging/MessageBroker.hpp"

struct TestStruct1 { int id = 1; };
struct TestStruct2 { int id = 2; };

void testCallback1(const TestStruct1& testStruct1) { std::cout << testStruct1.id << std::endl; }
void testCallback2(const TestStruct2& testStruct2) { std::cout << testStruct2.id << std::endl; }

/**
 * Test to subscribe to an event manager with a single message object
 * type to verify that the subscriber ID is 0.
 */
TEST(MessageBrokerTests, TestSubscribeCorrectIDOneType) {
    MessageBroker<TestStruct1> messageBroker;

    size_t id = messageBroker.subscribe(&testCallback1);
    EXPECT_EQ(0, id);
}

/**
 * Test to subscribe to an event manager with two message object
 * types to verify that the subscriber ID of type 1 is 0, and the
 * subscriber ID of type 2 is 1.
 */
TEST(MessageBrokerTests, TestSubscribeCorrectIDTwoTypes) {
    MessageBroker messageBroker;

    size_t id1 = messageBroker.subscribe<TestStruct1>(&testCallback1);
    size_t id2 = messageBroker.subscribe<TestStruct2>(&testCallback2);

    EXPECT_EQ(0, id1);
    EXPECT_EQ(1, id2);
}