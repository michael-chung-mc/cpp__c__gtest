cmake_minimum_required(VERSION 3.27.0)
project(wip__cpp__c__gtest VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_COMPILER g++)

include(CTest)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(src)