cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(parserSourceCode ../jsonparser.cpp)
add_executable(parserTest parser_test.cpp)

target_link_libraries(parserTest ${GTEST_LIBRARIES} pthread parserSourceCode)