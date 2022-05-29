cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME network)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE TEST_FILES test/*.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

add_executable(${PROJECT_NAME}_test ${TEST_FILES})
target_include_directories(${PROJECT_NAME}_test PRIVATE include)
target_link_libraries(${PROJECT_NAME}_test PUBLIC ${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
