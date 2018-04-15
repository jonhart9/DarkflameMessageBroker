#include <iostream>
#include "src/messaging/MessageEventService.hpp"

struct TestStruct1 {
    int id = 1;
};

void testCallback1(const TestStruct1& testStruct1) {

}

int main(int argc, char ** argv) {

    MessageEventService eventService;
    size_t subscriberID = eventService.subscribe<TestStruct1>(&testCallback1);

    std::cout << subscriberID << std::endl;

    bool didUnsubscribe = eventService.unsubscribe<TestStruct1>(subscriberID);

    std::cout << didUnsubscribe << std::endl;

    return 0;
}