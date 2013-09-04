cmake_minimum_required(VERSION 2.6)
project(gengine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

set(CMAKE_CXX_FLAGS "-std=c++11")

# Compiler-specific C++11 activation.
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
        message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater.")
    endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
else ()
    message(FATAL_ERROR "Your C++ compiler does not support C++11.")
endif ()

# Find OpenGL
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

# Find SFML
find_package(SFML 2 COMPONENTS system graphics window audio REQUIRED)

# Find Boost.
find_package(Boost COMPONENTS system REQUIRED)

# And threads.
find_package (Threads)

# Set executable output path
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(LIBRARY_OUTPUT_PATH ${gengine_SOURCE_DIR}/bin/debug)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(LIBRARY_OUTPUT_PATH ${gengine_SOURCE_DIR}/bin/release)
endif()

# Add include directories
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${SQLITE3_INCLUDE_DIR})

# Add the source directory
 file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
# add_subdirectory(src)
# the file() will be moved into each individual module so that we build all the different modules we need.
# TODO: Finish this and make it work http://www.cmake.org/Wiki/CMake/Tutorials/Object_Library

add_library(gengine ${SOURCE_FILES})

target_link_libraries(gengine ${OPENGL_LIBRARIES})
target_link_libraries(gengine ${GLEW_LIBRARIES})
# We need to link to Winsock if we're on Windows
if(WIN32)
  target_link_libraries(gengine wsock32 ws2_32)
endif()
target_link_libraries(gengine ${Boost_LIBRARIES})
target_link_libraries(gengine ${SFML_SYSTEM_LIBRARY_RELEASE} ${SFML_GRAPHICS_LIBRARY_RELEASE} ${SFML_WINDOW_LIBRARY_RELEASE} ${SFML_AUDIO_LIBRARY_RELEASE})
target_link_libraries(gengine ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(gengine ${SQLITE3_LIBRARIES})
