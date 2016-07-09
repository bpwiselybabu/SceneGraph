# - Find GLEW
# Find the native GLEW headers and libraries.
#
#  set( GLEW_USE_STATIC_LIBS ON ) - forces use of static library (libGLEW.a)
#  GLEW_INCLUDE_DIR -  where to find GLEW.h, etc.
#  GLEW_LIBRARIES    - List of libraries when using GLEW.
#  GLEW_FOUND        - True if GLEW found.

# Look for the header file.
FIND_PATH(GLEW_INCLUDE_DIR NAMES GL/glew.h
  PATHS 
  /opt/local/include
  $ENV{CPATH} )
MARK_AS_ADVANCED(GLEW_INCLUDE_DIR)

# Look for the library.
FIND_LIBRARY( GLEW_LIBRARY NAMES GLEW glew32
  PATHS 
  /opt/local/lib
  $ENV{LD_LIBRARY_PATH}
  $ENV{LIBRARY_PATH} 
  /usr/lib/
)

if( GLEW_USE_STATIC_LIBS ) 
  # a bit hacky
  STRING( REGEX REPLACE ".so" ".a" GLEW_LIBRARY ${GLEW_LIBRARY} )
endif()
MARK_AS_ADVANCED(GLEW_LIBRARY)

IF( WIN32 AND PREFER_STATIC_LIBRARIES )
  FIND_LIBRARY( GLEW_STATIC_LIBRARY NAMES glew32_static
    PATHS  $ENV{CPATH} )
  MARK_AS_ADVANCED(GLEW_STATIC_LIBRARY)
ENDIF( WIN32 AND PREFER_STATIC_LIBRARIES )
IF( GLEW_LIBRARY OR GLEW_STATIC_LIBRARY )
  SET( GLEW_LIBRARIES_FOUND 1 )
ENDIF( GLEW_LIBRARY OR GLEW_STATIC_LIBRARY )

# Copy the results to the output variables.
IF(GLEW_INCLUDE_DIR AND GLEW_LIBRARIES_FOUND)
  SET(GLEW_FOUND 1)
  IF( WIN32 AND PREFER_STATIC_LIBRARIES AND GLEW_STATIC_LIBRARY )
    SET(GLEW_LIBRARIES ${GLEW_STATIC_LIBRARY})
    SET( GLEW_STATIC 1 )
  ELSE( WIN32 AND PREFER_STATIC_LIBRARIES AND GLEW_STATIC_LIBRARY )
    SET(GLEW_LIBRARIES ${GLEW_LIBRARY})
  ENDIF( WIN32 AND PREFER_STATIC_LIBRARIES AND GLEW_STATIC_LIBRARY )
  SET(GLEW_INCLUDE_DIR ${GLEW_INCLUDE_DIR})
ELSE(GLEW_INCLUDE_DIR AND GLEW_LIBRARIES_FOUND)
  SET(GLEW_FOUND 0)
  SET(GLEW_LIBRARIES)
  SET(GLEW_INCLUDE_DIR)
ENDIF(GLEW_INCLUDE_DIR AND GLEW_LIBRARIES_FOUND)

IF(GLEW_FOUND)
  IF(NOT GLEW_FIND_QUIETLY)
    MESSAGE(STATUS "Found GLEW lib: ${GLEW_LIBRARY}")
    MESSAGE(STATUS "Found GLEW include: ${GLEW_INCLUDE_DIR}")
  ENDIF(NOT GLEW_FIND_QUIETLY)
ELSE(GLEW_FOUND)
  IF(GLEW_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find GLEW library")
  ENDIF(GLEW_FIND_REQUIRED)
ENDIF(GLEW_FOUND)


