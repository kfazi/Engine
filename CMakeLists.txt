PROJECT(Engine)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(ENGINE_NAME "engine")
SET(GAME_NAME "test")
SET(COMPANY_NAME "testcompany")
SET(ENGINESRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/enginesrc")
SET(FRAMEWORKSRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/frameworksrc")
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_scripts")

FIND_PACKAGE(Boost 1.36.0 COMPONENTS thread signals date_time REQUIRED)
FIND_PACKAGE(OIS REQUIRED)
FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
	ADD_CUSTOM_TARGET(engine_docs ${DOXYGEN_EXECUTABLE} "${CMAKE_SOURCE_DIR}/doxygen.conf" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMENT "Generating engine's documentation")
ELSE(DOXYGEN_FOUND)
	ADD_CUSTOM_TARGET(engine_docs COMMENT "Doxygen not found.")
ENDIF(DOXYGEN_FOUND)

# System specific setup
IF(WIN32)
    IF(MSVC)
        # This option is to enable the /MP switch for Visual Studio 2005 and above compilers
        OPTION(WIN32_USE_MP "Set to ON to build projects with the /MP option (Visual Studio 2005 and above)." OFF)
        MARK_AS_ADVANCED(WIN32_USE_MP)
        IF(WIN32_USE_MP)
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        ENDIF(WIN32_USE_MP)

		# Disable exceptions handling
		STRING(REGEX REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

		# Disable RTTI
		STRING(REGEX REPLACE "/GR+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
		LIST(APPEND COMMON_DEFINITIONS "BOOST_NO_TYPEID")
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")

        # Turn off various warnings
		# 4530 - C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc
		#        C++ exception handling was used but /EHsc was not selected.
		foreach(warning 4530 4251)
			SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd${warning}")
		endforeach(warning)

        # More MSVC specific compilation flags
		LIST(APPEND COMMON_DEFINITIONS "_SCL_SECURE_NO_WARNINGS")
		LIST(APPEND COMMON_DEFINITIONS "_CRT_SECURE_NO_DEPRECATE")
		LIST(APPEND COMMON_DEFINITIONS "_UNICODE")
		LIST(APPEND COMMON_DEFINITIONS "UNICODE")
    ENDIF(MSVC)
	LIST(APPEND COMMON_DEFINITIONS "WINDOWS")
ENDIF(WIN32)

IF(UNIX)
	LIST(APPEND COMMON_DEFINITIONS "UNIX")
ENDIF(UNIX)

LIST(APPEND COMMON_DEFINITIONS "ENGINE_NAME=\"${ENGINE_NAME}\"")
LIST(APPEND COMMON_DEFINITIONS "COMPANY_NAME=\"${COMPANY_NAME}\"")
LIST(APPEND COMMON_DEFINITIONS "GAME_NAME=\"${GAME_NAME}\"")

INCLUDE("CMakeListsEngine.txt")
INCLUDE("CMakeListsFramework.txt")
SOURCE_GROUP("" REGULAR_EXPRESSION ".*")

# EOF
