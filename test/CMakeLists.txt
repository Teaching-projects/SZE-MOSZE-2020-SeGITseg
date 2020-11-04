cmake_minimum_required(VERSION 2.6)
project(UnitTests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(unitTests unit_tests.cpp ../JSON.cpp ../Hero.cpp ../Monster.cpp))

target_link_libraries(unitTests ${GTEST_LIBRARIES} pthread)
