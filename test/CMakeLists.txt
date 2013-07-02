# LibCompetitive unit testing
cmake_minimum_required(VERSION 2.8)

project(LibCompetitive)

# Add gtest
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/gtest/include")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/gtest")
add_library(gtest STATIC "${PROJECT_SOURCE_DIR}/thirdparty/gtest/src/gtest-all.cc")

# Add library root as include directory
include_directories("${PROJECT_SOURCE_DIR}/..")

# Add compilation flags
set(CMAKE_CXX_FLAGS "-g -Wall")

# Add unit test files
file(GLOB_RECURSE test_src "${PROJECT_SOURCE_DIR}/unittest/*.cpp")
file(GLOB_RECURSE util_src "${PROJECT_SOURCE_DIR}/utility/*.cpp")
add_executable(libcompetitive_test ${test_src} ${util_src})
target_link_libraries(libcompetitive_test gtest pthread)

