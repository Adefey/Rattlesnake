project(libs)
cmake_minimum_required(VERSION 3.16)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(data_processing)
add_subdirectory(network)
