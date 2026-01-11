cmake_minimum_required(VERSION 3.10)

project(comock_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    comock_test/test_main.cpp
    comock_test/test_interface.cpp
    comock_test/test_class.cpp
)

set(HEADERS
    comock/comock.h
)

add_executable(comock_test
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(comock_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

source_group("src" FILES ${SOURCES} ${HEADERS})

enable_testing()

add_test(NAME comock_test COMMAND comock_test)
