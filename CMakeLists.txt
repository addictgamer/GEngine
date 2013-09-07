cmake_minimum_required(VERSION 2.6)
project(gengine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

find_package(CXX11 REQUIRED)
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS} -Wall")
set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CXX11_FLAGS}")
set ( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${CXX11_FLAGS}")
set ( CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${CXX11_FLAGS}")


# Find OpenGL
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

# Find SFML
find_package(SFML 2 COMPONENTS system graphics window audio REQUIRED)

# Find Boost.
find_package(Boost COMPONENTS system REQUIRED)

# And threads.
find_package(Threads)

# Find SQLite
find_package(SQLite)

# And finally, CEGUI TODO: Add necessary components
find_package(CEGUI REQUIRED)

# Add include directories
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${SQLITE3_INCLUDE_DIR})
include_directories("${CEGUI_INCLUDE_DIR}/..")

include_directories("${PROJECT_BINARY_DIR}/src/")

configure_file (${PROJECT_SOURCE_DIR}/src/build_config.hpp.in ${PROJECT_BINARY_DIR}/src/build_config.hpp )

# Add the source directory
file(GLOB_RECURSE gengine_SOURCE_FILES src/*.cpp src/*.hpp)
# add_subdirectory(src)
# the file() will be moved into each individual module so that we build all the different modules we need.
# TODO: Finish this and make it work http://www.cmake.org/Wiki/CMake/Tutorials/Object_Library

add_library(gengine ${gengine_SOURCE_FILES} ${PROJECT_BINARY_DIR}/src/build_config.hpp)

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
target_link_libraries(gengine ${CEGUI_LIBRARIES})

install(TARGETS gengine
  ARCHIVE DESTINATION lib COMPONENT Development
  LIBRARY DESTINATION lib COMPONENT Runtime
)

file(GLOB_RECURSE gengine_HEADER_FILES RELATIVE ${PROJECT_SOURCE_DIR}/src src/*.hpp)
list(REMOVE_ITEM gengine_HEADER_FILES src/internal_header.hpp)
foreach(HEADER ${gengine_HEADER_FILES})
  get_filename_component(HEADER_DIR "${HEADER}" PATH) # Ugly hack because CMake can't currently install headers while preserving directory structure <I think>
  install(FILES src/${HEADER} DESTINATION include/GEngine/${HEADER_DIR})
endforeach(HEADER gengine_HEADER_FILES)
install(FILES ${PROJECT_BINARY_DIR}/src/build_config.hpp DESTINATION include/GEngine/)
