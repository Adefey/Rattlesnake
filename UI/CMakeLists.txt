cmake_minimum_required(VERSION 3.8)
project(Rattlesnake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})

add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -fPIC")

file(GLOB_RECURSE SOURCES Sources/*.cpp)
file(GLOB_RECURSE TESTS Tests/*.cpp)

add_library(UI ${SOURCES})
target_include_directories(UI PRIVATE Headers)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(UITest ${TESTS})
target_include_directories(UITest PRIVATE Headers)
target_link_libraries(UITest PUBLIC ${GTEST_LIBRARIES})

#add_subdirectory(Tests)