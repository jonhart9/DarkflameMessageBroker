#include <iostream>
#include <unistd.h>

#include "src/messaging/MessageEventService.hpp"

struct TestStruct1 { };

struct TestStruct2 { };

static int id = 0;

void testCallback1(const TestStruct1& struct1) {
    std::cout << id++ << std::endl;
}

void testCallback2(const TestStruct2& struct2) {
    std::cout << "bob" << std::endl;
}

void testCallback3(const TestStruct1& struct1) {
    std::cout << "joe" << std::endl;
}

int main(int argc, char ** argv) {

    MessageEventService eventService;
    size_t subscriberID = eventService.subscribe<TestStruct1>(&testCallback1);
    size_t subscriber2 = eventService.subscribe<TestStruct2>(&testCallback2);
    size_t subscriber3 = eventService.subscribe<TestStruct1>(&testCallback3);

    std::cout << subscriberID << std::endl;

    for (int i = 0; i < 5; ++i) {
        eventService.broadcast(TestStruct1());

        sleep(5);

        eventService.update();
    }

    eventService.broadcast(TestStruct2());
    eventService.update();

    bool didUnsubscribe = eventService.unsubscribe<TestStruct1>(subscriberID);

    std::cout << didUnsubscribe << std::endl;

    for (int i = 0; i < 5; ++i) {
        eventService.broadcast(TestStruct1());

        sleep(5);

        eventService.update();
    }

    return 0;
}