cmake_minimum_required(VERSION 3.19)
project(unit_test)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY  https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        fmt_lib
        GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
        GIT_TAG 8.0.1
)
FetchContent_MakeAvailable(fmt_lib)

#FetchContent_Declare(
#        workflow
#        GIT_REPOSITORY  https://github.com/sogou/workflow.git
#        GIT_TAG v0.9.8
#)
#FetchContent_MakeAvailable(workflow)

#find_library(LIBRT rt)
#find_package(OpenSSL REQUIRED)
#include_directories(${OPENSSL_INCLUDE_DIR})

#message(dssl ${OPENSSL_INCLUDE_DIR})
#message(dflow ${WORKFLOW_INCLUDE_DIR})

#if (APPLE)
#    set(WORKFLOW_LIB workflow pthread OpenSSL::SSL OpenSSL::Crypto)
#else ()
#    set(WORKFLOW_LIB workflow ${LIBRT})
#endif ()


add_subdirectory(src)

enable_testing()
add_subdirectory(test)
