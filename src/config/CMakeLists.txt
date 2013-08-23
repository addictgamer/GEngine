cmake_minimum_required(VERSION 2.6)
project(gengine)

file(GLOB_RECURSE CONFIG_srcs ./*.cpp)

add_library(config ${CONFIG_srcs})

# TODO: Finish this and make it work http://www.cmake.org/Wiki/CMake/Tutorials/Object_Library
