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

file(GLOB_RECURSE SOURCE_FILES ../libs/data_processing/src/*.cpp)
add_library(data_processing ${SOURCE_FILES})
target_include_directories(data_processing PRIVATE ../libs/data_processing/include)

add_library(UI ${SOURCES})
target_include_directories(UI PRIVATE Headers ../libs/data_processing/include)
target_link_libraries(UI data_processing)

file(GLOB_RECURSE SOURCE_FILES ../libs/network/src/*.cpp)
add_library(network ${SOURCE_FILES})
target_include_directories(network PRIVATE ../libs/network/include)
target_include_directories(UI PRIVATE ../libs/network/include)
target_link_libraries(UI network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE HEADERS ../UI/Headers/*.h)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/Sources/rattlesnake-ico.qrc")

set(RESOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Sources/rattlesnake-ico.rcc"
)

add_executable(Rattlesnake main.cpp ${SOURCES} ${HEADERS} ${APP_ICON_RESOURCE_WINDOWS} ${RESOURCES})

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

target_include_directories(Rattlesnake PRIVATE Headers ../libs/data_processing/include)
target_include_directories(Rattlesnake PRIVATE ../libs/data_processing/include)
target_include_directories(Rattlesnake PRIVATE ../libs/network/include)
target_link_libraries(Rattlesnake data_processing)
target_link_libraries(Rattlesnake network)
target_link_libraries(Rattlesnake Qt5::Widgets)
target_link_libraries(Rattlesnake Qt5::Core)
target_link_libraries(Rattlesnake Qt5::Gui)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(UITest ${TESTS})
set (CMAKE_CXX_FLAGS "-DQT_NO_VERSION_TAGGING -fPIC")
target_include_directories(UITest PRIVATE Headers ../libs/data_processing/include ../libs/network/include)
target_link_libraries(UITest PUBLIC ${GTEST_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} pthread data_processing network UI)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Sources/cfg.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
