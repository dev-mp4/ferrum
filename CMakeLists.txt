cmake_minimum_required(VERSION 3.10)
project(ferrum)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(ferrum ${SRC_FILES})

target_include_directories(ferrum PRIVATE src)