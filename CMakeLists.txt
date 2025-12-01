cmake_minimum_required(VERSION 3.10)
project(ferrum)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(ferrum ${SRC_FILES})

target_include_directories(ferrum PRIVATE src)