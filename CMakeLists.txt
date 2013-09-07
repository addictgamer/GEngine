cmake_minimum_required(VERSION 2.6)
project(GEngine)

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

# And CEGUI. TODO: Add necessary components
find_package(CEGUI REQUIRED)

# Find SQLite if enabled
if ("${GEngine_USE_SQLITE}" STREQUAL "")
  set (GEngine_USE_SQLITE TRUE CACHE BOOL "Whether to enable SQLite support")
endif ("${GEngine_USE_SQLITE}" STREQUAL "")
if (GEngine_USE_SQLITE)
  find_package(SQLite)
  if (NOT SQLITE3_FOUND)
    message(FATAL_ERROR "Could not find SQLite. Use -DGEngine_USE_SQLITE=FALSE to disable SQLite support.")
  endif (NOT SQLITE3_FOUND)
  include_directories(${SQLITE3_INCLUDE_DIR})
endif(GEngine_USE_SQLITE)

# Add include directories
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})

include_directories("${CEGUI_INCLUDE_DIR}/..")

include_directories("${PROJECT_BINARY_DIR}/src/")

configure_file (${PROJECT_SOURCE_DIR}/src/build_config.hpp.in ${PROJECT_BINARY_DIR}/src/build_config.hpp )

add_subdirectory(src)

add_library(gengine ${GEngine_SOURCES} ${PROJECT_BINARY_DIR}/src/build_config.hpp)

target_link_libraries(gengine ${OPENGL_LIBRARIES})
target_link_libraries(gengine ${GLEW_LIBRARIES})
# We need to link to Winsock if we're on Windows
if(WIN32)
  target_link_libraries(gengine wsock32 ws2_32)
endif()
target_link_libraries(gengine ${Boost_LIBRARIES})
target_link_libraries(gengine ${SFML_SYSTEM_LIBRARY_RELEASE} ${SFML_GRAPHICS_LIBRARY_RELEASE} ${SFML_WINDOW_LIBRARY_RELEASE} ${SFML_AUDIO_LIBRARY_RELEASE})
target_link_libraries(gengine ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(gengine ${CEGUI_LIBRARIES} ${CEGUI_RENDERER_COMPONENTS})

if (GEngine_USE_SQLITE)
  target_link_libraries(gengine ${SQLITE3_LIBRARIES})
endif (GEngine_USE_SQLITE)

install(TARGETS gengine
  ARCHIVE DESTINATION lib COMPONENT Development
  LIBRARY DESTINATION lib COMPONENT Runtime
)

foreach(HEADER ${GEngine_HEADERS})
  if (NOT ${HEADER} MATCHES "internal_header.hpp")
    string(REPLACE "${PROJECT_SOURCE_DIR}/src/" "" HEADER ${HEADER})
    get_filename_component(HEADER_DIR "${HEADER}" PATH) # Ugly hack because CMake can't currently install headers while preserving directory structure <I think>
    get_filename_component(HEADER_NAME "${HEADER}" NAME)
    install(FILES "src/${HEADER}" DESTINATION "include/GEngine/${HEADER_DIR}")
  endif(NOT ${HEADER} MATCHES "internal_header.hpp")
endforeach(HEADER GEngine_HEADERS)
install(FILES ${PROJECT_BINARY_DIR}/src/build_config.hpp DESTINATION include/GEngine/)
