# Finds CEGUI with specified components.

include (FindPackageHandleStandardArgs)

set(POSSIBLE_HOMEVAR_NAMES
  "CEGUI_HOME"
  "CEGUIHOME"
  "CEGUI_ROOT"
  "CEGUIROOT"
)
foreach (NAME ${POSSIBLE_HOMEVAR_NAMES})
  if (NOT "${${NAME}}" STREQUAL "")
    set(CEGUI_HOME "${${NAME}}")
    break()
  endif ()
  if (NOT $ENV{${NAME}} STREQUAL "")
    set(CEGUI_HOME "$ENV{${NAME}}")
    break()
  endif()
endforeach (NAME)
set (SEARCH_PATHS
  "${CEGUI_HOME}"
  "${CEGUI_HOME}"
  /usr/local
  /usr
)

find_path (CEGUI_INCLUDE_DIR "CEGUI.h" PATHS ${SEARCH_PATHS} PATH_SUFFIXES include include/CEGUI include/cegui-0/CEGUI)

list (APPEND CEGUI_FIND_COMPONENTS "Base")
list (REMOVE_DUPLICATES CEGUI_FIND_COMPONENTS)
set (CEGUI_LIBRARIES "")
set (CEGUI_LIBRARY_VARS "")
foreach (COMP ${CEGUI_FIND_COMPONENTS})
  find_library(CEGUI_${COMP}_LIBRARY
    NAMES CEGUI${COMP} CEGUI${COMP}-0
    PATHS ${SEARCH_PATHS}
  )
  set (CEGUI_${COMP}_LIBRARY ${CEGUI_${COMP}_LIBRARY} CACHE FILEPATH "Path to CEGUI component ${COMP}")
  find_package_handle_standard_args(CEGUI_${COMP} FOUND_VAR CEGUI_${COMP}_FOUND REQUIRED_VARS CEGUI_${COMP}_LIBRARY)
  list (APPEND CEGUI_LIBRARIES ${CEGUI_${COMP}_LIBRARY})
  list (APPEND CEGUI_LIBRARY_VARS CEGUI_${COMP}_LIBRARY)
endforeach (COMP)

find_package_handle_standard_args(CEGUI DEFAULT_MSG CEGUI_INCLUDE_DIR CEGUI_LIBRARIES ${CEGUI_LIBRARY_VARS})
