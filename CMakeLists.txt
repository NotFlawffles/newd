cmake_minimum_required(VERSION 3.5)

project(newd)

include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(newd ${SOURCES})
