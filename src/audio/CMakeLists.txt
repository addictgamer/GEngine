add_subdirectory(Music)

list(APPEND GEngine_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/audio_fmod.cpp"
)
list(APPEND GEngine_HEADERS
  "${CMAKE_CURRENT_SOURCE_DIR}/audio.hpp"
)

set(GEngine_SOURCES ${GEngine_SOURCES} PARENT_SCOPE)
set(GEngine_HEADERS ${GEngine_HEADERS} PARENT_SCOPE)

