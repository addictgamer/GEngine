# - Try to find the SDL library
# Once done this will define
#
#  SDL2_FOUND - system has SDL
#  SDL2_INCLUDE_DIR - the SDL include directory
#  SDL2_LIBRARIES - The libraries needed to use SDL

if(SDL2_INCLUDE_DIR AND SDL2_LIBRARIES AND
   SDL2_IMAGE_INCLUDE_DIR AND SDL2_IMAGE_LIBRARIES AND
   SDL2_MIXER_INCLUDE_DIR AND SDL2_MIXER_LIBRARIES)
   set(SDL2_FOUND TRUE)
else(SDL2_INCLUDE_DIR AND SDL2_LIBRARIES AND
   SDL2_IMAGE_INCLUDE_DIR AND SDL2_IMAGE_LIBRARIES AND
   SDL2_MIXER_INCLUDE_DIR AND SDL2_MIXER_LIBRARIES)

FIND_PATH(SDL2_INCLUDE_DIR SDL.h
   /usr/include
   /usr/local/include
   $ENV{SDL2ROOT}/include/SDL
   $ENV{SDL2_ROOT}/include/SDL
   $ENV{SDL2_DIR}/include/SDL
   $ENV{SDL2ROOT}/include
   $ENV{SDL2_ROOT}/include
   $ENV{SDL2_DIR}/include
   $ENV{SDL2ROOT}
   $ENV{SDL2_ROOT}
   $ENV{SDL2_DIR}
   [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup\\VC]/PlatformSDK/Include
)

FIND_PATH(SDL2_IMAGE_INCLUDE_DIR SDL_image.h
   /usr/include
   /usr/local/include
   $ENV{SDL2_IMAGEROOT}/include/SDL
   $ENV{SDL2_IMAGE_ROOT}/include/SDL
   $ENV{SDL2_IMAGE_DIR}/include/SDL
   $ENV{SDL2_IMAGEROOT}/include
   $ENV{SDL2_IMAGE_ROOT}/include
   $ENV{SDL2_IMAGE_DIR}/include
   $ENV{SDL2_IMAGEROOT}
   $ENV{SDL2_IMAGE_ROOT}
   $ENV{SDL2_IMAGE_DIR}
   [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup\\VC]/PlatformSDK/Include
)

FIND_PATH(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h
   /usr/include
   /usr/local/include
   $ENV{SDL2_MIXERROOT}/include/SDL
   $ENV{SDL2_MIXER_ROOT}/include/SDL
   $ENV{SDL2_MIXER_DIR}/include/SDL
   $ENV{SDL2_MIXERROOT}/include
   $ENV{SDL2_MIXER_ROOT}/include
   $ENV{SDL2_MIXER_DIR}/include
   $ENV{SDL2_MIXERROOT}
   $ENV{SDL2_MIXER_ROOT}
   $ENV{SDL2_MIXER_DIR}
   [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup\\VC]/PlatformSDK/Include
)

FIND_LIBRARY(SDL2_LIBRARIES NAMES SDL2
   PATHS
   /usr/lib
   /usr/lib64
   /usr/local/lib
   /usr/local/lib64
   $ENV{SDL2ROOT}/lib
   $ENV{SDL2_ROOT}/lib
   $ENV{SDL2_DIR}/lib
   [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup\\VC]/PlatformSDK/Lib
   DOC "SDL2 library name"
)

FIND_LIBRARY(SDL2_IMAGE_LIBRARIES NAMES SDL_image
   PATHS
   /usr/lib
   /usr/lib64
   /usr/local/lib
   /usr/local/lib64
   $ENV{SDL2_IMAGEROOT}/.libs
   $ENV{SDL2_IMAGE_ROOT}/.libs
   $ENV{SDL2_IMAGE_DIR}/.libs
   $ENV{SDL2_IMAGEROOT}/lib
   $ENV{SDL2_IMAGE_ROOT}/lib
   $ENV{SDL2_IMAGE_DIR}/lib
   [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup\\VC]/PlatformSDK/Lib
   DOC "SDL2_image library name"
)

FIND_LIBRARY(SDL2_MIXER_LIBRARIES NAMES SDL2_mixer
   PATHS
   /usr/lib
   /usr/lib64
   /usr/local/lib
   /usr/local/lib64
   $ENV{SDL2_MIXERROOT}/.libs
   $ENV{SDL2_MIXER_ROOT}/.libs
   $ENV{SDL2_MIXER_DIR}/.libs
   $ENV{SDL2_MIXERROOT}/lib
   $ENV{SDL2_MIXER_ROOT}/libs
   $ENV{SDL2_MIXER_DIR}/lib
   [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup\\VC]/PlatformSDK/Lib
   DOC "SDL2_mixer library name"
)

if(SDL2_INCLUDE_DIR AND SDL2_LIBRARIES)
   set(SDL2_FOUND TRUE)
endif(SDL2_INCLUDE_DIR AND SDL2_LIBRARIES)

if(SDL2_IMAGE_INCLUDE_DIR AND SDL2_IMAGE_LIBRARIES)
   set(SDL2_IMAGE_FOUND TRUE)
endif(SDL2_IMAGE_INCLUDE_DIR AND SDL2_IMAGE_LIBRARIES)

if(SDL2_MIXER_INCLUDE_DIR AND SDL2_MIXER_LIBRARIES)
   set(SDL2_MIXER_FOUND TRUE)
endif(SDL2_MIXER_INCLUDE_DIR AND SDL2_MIXER_LIBRARIES)


if(SDL2_FOUND)
   if(NOT SDL2_FIND_QUIETLY)
      message(STATUS "Found SDL: ${SDL2_LIBRARIES}")
   endif(NOT SDL2_FIND_QUIETLY)
else(SDL2_FOUND)
   if(SDL2_FIND_REQUIRED)
      message(FATAL_ERROR "could NOT find SDL! Make sure that the header files are in an 'include/SDL'-directory.")
   endif(SDL2_FIND_REQUIRED)
endif(SDL2_FOUND)

if(SDL2_IMAGE_FOUND)
   if(NOT SDL2_FIND_QUIETLY)
      message(STATUS "Found SDL2_image: ${SDL2_IMAGE_LIBRARIES}")
   endif(NOT SDL2_FIND_QUIETLY)
else(SDL2_IMAGE_FOUND)
   if(SDL2_FIND_REQUIRED)
      message(FATAL_ERROR "could NOT find SDL_image! Make sure that the header files are in an 'include/SDL'-directory.")
   endif(SDL2_FIND_REQUIRED)
endif(SDL2_IMAGE_FOUND)

if(SDL2_MIXER_FOUND)
   if(NOT SDL2_FIND_QUIETLY)
      message(STATUS "Found SDL2_mixer: ${SDL2_MIXER_LIBRARIES}")
   endif(NOT SDL2_FIND_QUIETLY)
else(SDL2_MIXER_FOUND)
   if(SDL2_FIND_REQUIRED)
      message(FATAL_ERROR "could NOT find SDL_mixer! Make sure that the header files are in an 'include/SDL'-directory.")
   endif(SDL2_FIND_REQUIRED)
endif(SDL2_MIXER_FOUND)

MARK_AS_ADVANCED(SDL2_INCLUDE_DIR SDL2_LIBRARIES SDL2_IMAGE_INCLUDE_DIR SDL2_IMAGE_LIBRARIES SDL2_MIXER_INCLUDE_DIR SDL2_MIXER_LIBRARIES)

endif(SDL2_INCLUDE_DIR AND SDL2_LIBRARIES AND
   SDL2_IMAGE_INCLUDE_DIR AND SDL2_IMAGE_LIBRARIES AND
   SDL2_MIXER_INCLUDE_DIR AND SDL2_MIXER_LIBRARIES)
