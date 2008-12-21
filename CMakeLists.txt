CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_scripts)

SET(CORE_SOURCES
	enginesrc/common.hpp
	enginesrc/config.hpp
	enginesrc/engine.cpp
	enginesrc/engine.hpp
	enginesrc/engineexception.hpp
	enginesrc/functionmanager.cpp
	enginesrc/functionmanager.hpp
	enginesrc/logger.hpp
	enginesrc/main.cpp
	enginesrc/time.cpp
	enginesrc/time.hpp
	enginesrc/useful.hpp
	enginesrc/windowscleanup.hpp
)
SOURCE_GROUP("enginesrc" FILES ${CORE_SOURCES})
LIST(APPEND SOURCES ${CORE_SOURCES})

SET(MATH_SOURCES
	enginesrc/math/vector3.cpp
	enginesrc/math/vector3.hpp
)
SOURCE_GROUP("enginesrc\\math" FILES ${MATH_SOURCES})
LIST(APPEND SOURCES ${MATH_SOURCES})

SET(OPERATING_SYSTEM_SOURCES
	enginesrc/operating_system/keyboardremap.hpp
	enginesrc/operating_system/systemdisplaymanager.hpp
	enginesrc/operating_system/systeminfo.hpp
	enginesrc/operating_system/systeminput.hpp
	enginesrc/operating_system/systemwindow.hpp
)
SOURCE_GROUP("enginesrc\\operating_system" FILES ${OPERATING_SYSTEM_SOURCES})
LIST(APPEND SOURCES ${OPERATING_SYSTEM_SOURCES})

SET(SCENE_SOURCES
	enginesrc/scene/scene.cpp
	enginesrc/scene/scene.hpp
	enginesrc/scene/scenemanager.cpp
	enginesrc/scene/scenemanager.hpp
	enginesrc/scene/sceneobject.hpp
)
SOURCE_GROUP("enginesrc\\scene" FILES ${SCENE_SOURCES})
LIST(APPEND SOURCES ${SCENE_SOURCES})

SET(OPERATING_SYSTEM_WINDOWS_SOURCES
	enginesrc/operating_system/windows/windowssystemdisplaymanager.cpp
	enginesrc/operating_system/windows/windowssystemdisplaymanager.hpp
	enginesrc/operating_system/windows/windowssystemwindow.cpp
	enginesrc/operating_system/windows/windowssystemwindow.hpp
	enginesrc/operating_system/windows/windowssysteminfo.cpp
	enginesrc/operating_system/windows/windowssysteminfo.hpp
)
SOURCE_GROUP("enginesrc\\operating_system\\windows" FILES ${OPERATING_SYSTEM_WINDOWS_SOURCES})
LIST(APPEND SOURCES ${OPERATING_SYSTEM_WINDOWS_SOURCES})

SET(OPERATING_SYSTEM_UNIX_SOURCES
	enginesrc/operating_system/unix/unixsystemdisplaymanager.cpp
	enginesrc/operating_system/unix/unixsystemdisplaymanager.hpp
	enginesrc/operating_system/unix/unixsystemwindow.cpp
	enginesrc/operating_system/unix/unixsystemwindow.hpp
	enginesrc/operating_system/unix/unixsystemmessagebox.hpp
	enginesrc/operating_system/unix/unixsysteminfo.cpp
	enginesrc/operating_system/unix/unixsysteminfo.hpp
)
SOURCE_GROUP("enginesrc\\operating_system\\unix" FILES ${OPERATING_SYSTEM_UNIX_SOURCES})
LIST(APPEND SOURCES ${OPERATING_SYSTEM_UNIX_SOURCES})

# System specific files
IF(WIN32)
	SET(SYSTEM_LIBRARIES
	)
	LIST(APPEND DEFINITIONS "-DWIN32 -DOPENGL -DDIRECTX")
ENDIF(WIN32)

IF(UNIX)
	SET(SYSTEM_LIBRARIES
		X11
		GL
	)
	LIST(APPEND DEFINITIONS "-DUNIX -DOPENGL")
ENDIF(UNIX)

SOURCE_GROUP("" REGULAR_EXPRESSION ".*")

FIND_PACKAGE(Boost 1.36.0 COMPONENTS thread signals date_time REQUIRED)
FIND_PACKAGE(OIS)

ADD_DEFINITIONS(${DEFINITIONS})
INCLUDE_DIRECTORIES(${OIS_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
ADD_EXECUTABLE(engine WIN32 ${SOURCES})
TARGET_LINK_LIBRARIES(engine ${OIS_LIBRARIES} ${Boost_LIBRARIES} ${SYSTEM_LIBRARIES})

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
	ADD_CUSTOM_TARGET(docs ${DOXYGEN_EXECUTABLE} doxygen.conf WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMENT "Generating documentation")
ELSE(DOXYGEN_FOUND)
	ADD_CUSTOM_TARGET(docs COMMENT "Doxygen not found.")
ENDIF(DOXYGEN_FOUND)

