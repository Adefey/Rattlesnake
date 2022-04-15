cmake_minimum_required(VERSION 3.14)
project(Rattlesnake)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -ldl)
target_include_directories(${PROJECT_NAME} PUBLIC ${UI_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)