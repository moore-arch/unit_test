cmake_minimum_required(VERSION 3.19)
project(demo)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt)

add_executable(unit_test UtilityTest.cpp TestMain.cpp)

target_link_libraries(unit_test gtest fmt)
