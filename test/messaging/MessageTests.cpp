/**
 * A test case file to verify the integrity of the {@link Message} class.
 */
#include <gtest/gtest.h>

#include "../../src/messaging/message/Message.hpp"

/** A test structure */
struct TestStruct1 { int id = 1; };
struct TestStruct2 { int id = 2; };

/**
 * Test to verify that a message created with type TestStruct1
 * is valid.
 */
TEST(MessageTests, MessageConstructionStruct1) {
    TestStruct1 testStruct1;
    Message<TestStruct1> message(testStruct1);

    EXPECT_EQ(1, testStruct1.id);
    EXPECT_EQ(1, message.getMessageType().id);
}

/**
 * Test to verify that the static unique type of the first created
 * Message<> object in the program in '0'.
 */
TEST(MessageTests, MessageTypeStruct1Test1) {
    EXPECT_EQ(0, Message<TestStruct1>::getUniqueType());
}

/**
 * Test to verify that a message created with the TestStruct2
 * type is also valid.
 */
TEST(MessageTests, MessageConstructionStruct2) {
    TestStruct2 testStruct2;
    Message<TestStruct2> message(testStruct2);

    EXPECT_EQ(2, testStruct2.id);
    EXPECT_EQ(2, message.getMessageType().id);
}

/**
 * Test to verify that the static unique type for the second
 * created Message<> object is '1'.
 */
TEST(MessageTests, MessageTypeStruct2Test1) {
    EXPECT_EQ(1, Message<TestStruct2>::getUniqueType());
}

/**
 * Test to re-verify that after creating multiple types of
 * the Message<> object, the static unique identifier of the
 * first struct (TestStruct1) is still '0'.
 */
TEST(MessageTests, MessageTypeStruct1Test2) {
    EXPECT_EQ(0, Message<TestStruct1>::getUniqueType());
}