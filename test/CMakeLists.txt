cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(parserSourceCode ../jsonparser.cpp)
add_library(unitSourceCode ../unit.cpp)
add_executable(unitTests unit_tests.cpp)

target_link_libraries(unitTests ${GTEST_LIBRARIES} pthread parserSourceCode unitSourceCode)