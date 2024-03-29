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

# Check if population has already been performed
#FetchContent_GetProperties(depname)
#if(NOT depname_POPULATED)
#    # Fetch the content using previously declared details
#    FetchContent_Populate(depname)
#
#    # Set custom variables, policies, etc.
#    # ...
#
#    # Bring the populated content into the build
#    add_subdirectory(${depname_SOURCE_DIR} ${depname_BINARY_DIR})
#endif()

FetchContent_Declare(
        fmt_lib
        GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
        GIT_TAG 8.0.1
)
FetchContent_MakeAvailable(fmt_lib)

FetchContent_Declare(
        workflow
        GIT_REPOSITORY  https://github.com/sogou/workflow.git
        GIT_TAG v0.9.8
)
FetchContent_MakeAvailable(workflow)
include_directories(${workflow_SOURCE_DIR}/_include)

find_library(LIBRT rt)
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

link_directories(${WORKFLOW_LIB_DIR})


set(WORKFLOW_LIB workflow pthread OpenSSL::SSL OpenSSL::Crypto)

add_subdirectory(src)

# 不定义则默认跳过测试，可以使用include(CTest)代替
enable_testing()
include_directories(src)
add_subdirectory(test)
