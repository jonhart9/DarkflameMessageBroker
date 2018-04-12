cmake_minimum_required(VERSION 3.10)
project(DarkflameEventManager)

# Make sure conanbuildinfo.cmake exists
# If it does not, run `conan install . -s build_type={Debug|Release} --install-folder=cmake-build-{debug|release}`
if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install ")
endif()

set(CMAKE_CXX_STANDARD 17)
add_executable(DarkflameEventManager main.cpp src/messaging/MessageBroker.cpp src/messaging/MessageBroker.hpp src/messaging/message/IMessage.hpp src/messaging/message/Message.hpp)
add_executable(DarkflameEventManagerTests test/messaging/MessageTests.cpp)

target_link_libraries(DarkflameEventManager ${CONAN_LIBS})
target_link_libraries(DarkflameEventManagerTests ${CONAN_LIBS})