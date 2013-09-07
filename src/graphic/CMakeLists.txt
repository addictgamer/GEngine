add_subdirectory(2d)
add_subdirectory(window)

list(APPEND GEngine_HEADERS
  "${CMAKE_CURRENT_SOURCE_DIR}/graphic.hpp"
)

set(GEngine_SOURCES ${GEngine_SOURCES} PARENT_SCOPE)
set(GEngine_HEADERS ${GEngine_HEADERS} PARENT_SCOPE)

