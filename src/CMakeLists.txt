cmake_minimum_required(VERSION 3.19)
project(demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(demo main.cpp Tools.cpp Tools.h)
target_link_libraries(demo fmt ${WORKFLOW_LIB})