cmake_minimum_required(VERSION 3.19)
project(unit_test)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt)

FILE(GLOB SRCS ../src/*.cpp)
#list(REMOVE_ITEM SRCS "*main.cpp")
list(FILTER SRCS EXCLUDE REGEX ".*main\\.cpp$")
FILE(GLOB TEST_SRCS *.cpp)

set(IMPL_SRCS ../src/QueueImpl.h)

message(srcs ******* ${SRCS} *******)

#set(SRC ../src/Tools.cpp)
#set(TEST_SRC TestMain.cpp ToolsTest.cpp UtilityTest.cpp)

add_executable(unit_test ${TEST_SRCS}  ${SRCS} ${IMPL_SRCS})
#add_executable(unit_test TestMain.cpp ToolsTest.cpp UtilityTest.cpp ../src/Tools.cpp )
target_link_libraries(unit_test gtest fmt)
