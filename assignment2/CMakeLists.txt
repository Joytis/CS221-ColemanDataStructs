cmake_minimum_required(VERSION 3.5)
project(assignment2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/
)

add_executable(assignment2 ${SOURCE_FILES})

add_custom_command(TARGET assignment2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/inventory $<TARGET_FILE_DIR:assignment2>/inventory)