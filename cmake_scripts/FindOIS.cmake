# Find OIS includes and library
#
# This module defines
#  OIS_INCLUDE_DIR - OIS includes path
#  OIS_LIBRARIES - OIS libraries
#  OIS_FOUND - is OIS present on this system

IF (OIS_LIBRARIES AND OIS_INCLUDE_DIR)
	SET(OIS_FIND_QUIETLY TRUE)
ENDIF (OIS_LIBRARIES AND OIS_INCLUDE_DIR)

IF (WIN32)
	MESSAGE(STATUS "Searching for OIS")
	FIND_PATH(OIS_INCLUDE_DIR OIS.h
		HINTS $ENV{OIS_HOME}
		PATHS $ENV{OIS_HOME}
		PATH_SUFFIXES include/OIS include includes includes/OIS
	)	
	FIND_LIBRARY(OIS_LIBRARIES 
		NAMES OIS ois OIS_static
		HINTS $ENV{OIS_HOME}
		PATHS $ENV{OIS_HOME}
		PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
	)
ELSE (WIN32)
	FIND_PACKAGE(PkgConfig)
	PKG_SEARCH_MODULE(OIS OIS /usr/pack/ois-1.0-sd/i686-debian-linux3.1/lib/pkgconfig/OIS.pc) # tardis specific hack
	SET(OIS_INCLUDE_DIR ${OIS_INCLUDE_DIRS})
	SET(OIS_LIB_DIR ${OIS_LIBDIR})
	SET(OIS_LIBRARIES ${OIS_LIBRARIES} CACHE STRING "")
ENDIF (WIN32)

SEPARATE_ARGUMENTS(OIS_INCLUDE_DIR)
SEPARATE_ARGUMENTS(OIS_LIBRARIES)

SET(OIS_INCLUDE_DIR ${OIS_INCLUDE_DIR} CACHE PATH "")
SET(OIS_LIBRARIES ${OIS_LIBRARIES} CACHE STRING "")

IF (OIS_INCLUDE_DIR AND OIS_LIBRARIES)
	SET(OIS_FOUND TRUE)
ENDIF (OIS_INCLUDE_DIR AND OIS_LIBRARIES)

IF (OIS_FOUND)
	IF (NOT OIS_FIND_QUIETLY)
		MESSAGE(STATUS "  libraries : ${OIS_LIBRARIES}")
		MESSAGE(STATUS "  includes  : ${OIS_INCLUDE_DIR}")
	ENDIF (NOT OIS_FIND_QUIETLY)
ELSE (OIS_FOUND)
	IF (OIS_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find OIS")
	ENDIF (OIS_FIND_REQUIRED)
ENDIF (OIS_FOUND)
