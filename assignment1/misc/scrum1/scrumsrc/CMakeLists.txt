cmake_minimum_required(VERSION 3.5)
project(assignment1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BookRecord.cpp)
add_executable(assignment1 ${SOURCE_FILES})