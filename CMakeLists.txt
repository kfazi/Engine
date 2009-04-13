CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(CMAKE_MODULE_PATH ${ENGINE_PATH}/cmake_scripts)

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
	ADD_CUSTOM_TARGET(engine_docs ${DOXYGEN_EXECUTABLE} ${ENGINE_PATH}/doxygen.conf WORKING_DIRECTORY ${ENGINE_PATH} COMMENT "Generating engine's documentation")
ELSE(DOXYGEN_FOUND)
	ADD_CUSTOM_TARGET(engine_docs COMMENT "Doxygen not found.")
ENDIF(DOXYGEN_FOUND)

SET(ENGINESRC_DIR ${ENGINE_PATH}/enginesrc)
SET(ENGINE_SOURCES "")
SET(ENGINE_DEFINITIONS "")
SET(ENGINE_INCLUDE_DIR "")
SET(ENGINE_LIBRARIES "")

SET(ENGINE_CORE_SOURCES
	${ENGINESRC_DIR}/common.hpp
	${ENGINESRC_DIR}/config.cpp
	${ENGINESRC_DIR}/config.hpp
	${ENGINESRC_DIR}/core.cpp
	${ENGINESRC_DIR}/core.hpp
	${ENGINESRC_DIR}/engine.hpp
	${ENGINESRC_DIR}/engineexception.hpp
	${ENGINESRC_DIR}/enginemain.hpp
	${ENGINESRC_DIR}/functionmanager.cpp
	${ENGINESRC_DIR}/functionmanager.hpp
	${ENGINESRC_DIR}/logger.hpp
	${ENGINESRC_DIR}/main.cpp
	${ENGINESRC_DIR}/string.cpp
	${ENGINESRC_DIR}/string.hpp
	${ENGINESRC_DIR}/time.cpp
	${ENGINESRC_DIR}/time.hpp
	${ENGINESRC_DIR}/useful.hpp
	${ENGINESRC_DIR}/windowscleanup.hpp
)
SOURCE_GROUP("engine\\enginesrc" FILES ${ENGINE_CORE_SOURCES})
LIST(APPEND ENGINE_SOURCES ${ENGINE_CORE_SOURCES})

SET(ENGINE_MATH_SOURCES
	${ENGINESRC_DIR}/math/math.hpp
	${ENGINESRC_DIR}/math/matrix4.cpp
	${ENGINESRC_DIR}/math/matrix4.hpp
	${ENGINESRC_DIR}/math/quaternion.cpp
	${ENGINESRC_DIR}/math/quaternion.hpp
	${ENGINESRC_DIR}/math/rect.hpp
	${ENGINESRC_DIR}/math/vector2.cpp
	${ENGINESRC_DIR}/math/vector2.hpp
	${ENGINESRC_DIR}/math/vector3.cpp
	${ENGINESRC_DIR}/math/vector3.hpp
	${ENGINESRC_DIR}/math/vector4.cpp
	${ENGINESRC_DIR}/math/vector4.hpp
	${ENGINESRC_DIR}/math/worldmatrix.hpp
)
SOURCE_GROUP("engine\\enginesrc\\math" FILES ${ENGINE_MATH_SOURCES})
LIST(APPEND ENGINE_SOURCES ${ENGINE_MATH_SOURCES})

SET(ENGINE_OPERATING_SYSTEM_SOURCES
	${ENGINESRC_DIR}/operating_system/keyboard.cpp
	${ENGINESRC_DIR}/operating_system/keyboard.hpp
	${ENGINESRC_DIR}/operating_system/mouse.hpp
	${ENGINESRC_DIR}/operating_system/pad.hpp
	${ENGINESRC_DIR}/operating_system/systemdirectories.hpp
	${ENGINESRC_DIR}/operating_system/systemdisplaymanager.hpp
	${ENGINESRC_DIR}/operating_system/systeminfo.hpp
	${ENGINESRC_DIR}/operating_system/systeminput.cpp
	${ENGINESRC_DIR}/operating_system/systeminput.hpp
	${ENGINESRC_DIR}/operating_system/systeminputcontroller.hpp
	${ENGINESRC_DIR}/operating_system/systeminputois.hpp
	${ENGINESRC_DIR}/operating_system/systemwindow.hpp
)
SOURCE_GROUP("engine\\enginesrc\\operating_system" FILES ${ENGINE_OPERATING_SYSTEM_SOURCES})
LIST(APPEND ENGINE_SOURCES ${ENGINE_OPERATING_SYSTEM_SOURCES})

SET(ENGINE_RENDERER_SOURCES
	${ENGINESRC_DIR}/renderer/rendertarget.hpp
)
SOURCE_GROUP("engine\\enginesrc\\renderer" FILES ${ENGINE_RENDERER_SOURCES})
LIST(APPEND ENGINE_SOURCES ${ENGINE_RENDERER_SOURCES})

SET(ENGINE_SCENE_SOURCES
	${ENGINESRC_DIR}/scene/camera.cpp
	${ENGINESRC_DIR}/scene/camera.hpp
	${ENGINESRC_DIR}/scene/freecamera.cpp
	${ENGINESRC_DIR}/scene/freecamera.hpp
	${ENGINESRC_DIR}/scene/scene.cpp
	${ENGINESRC_DIR}/scene/scene.hpp
	${ENGINESRC_DIR}/scene/scenemanager.cpp
	${ENGINESRC_DIR}/scene/scenemanager.hpp
	${ENGINESRC_DIR}/scene/sceneobject.hpp
	${ENGINESRC_DIR}/scene/targetedcamera.cpp
	${ENGINESRC_DIR}/scene/targetedcamera.hpp
)
SOURCE_GROUP("engine\\enginesrc\\scene" FILES ${ENGINE_SCENE_SOURCES})
LIST(APPEND ENGINE_SOURCES ${ENGINE_SCENE_SOURCES})

SET(ENGINE_OPERATING_SYSTEM_WINDOWS_SOURCES
	${ENGINESRC_DIR}/operating_system/windows/windowssystemdirectories.cpp
	${ENGINESRC_DIR}/operating_system/windows/windowssystemdirectories.hpp
	${ENGINESRC_DIR}/operating_system/windows/windowssystemdisplaymanager.cpp
	${ENGINESRC_DIR}/operating_system/windows/windowssystemdisplaymanager.hpp
	${ENGINESRC_DIR}/operating_system/windows/windowssysteminfo.cpp
	${ENGINESRC_DIR}/operating_system/windows/windowssysteminfo.hpp
	${ENGINESRC_DIR}/operating_system/windows/windowssystemwindow.cpp
	${ENGINESRC_DIR}/operating_system/windows/windowssystemwindow.hpp
	${ENGINESRC_DIR}/operating_system/windows/windowssystemwinmain.cpp
)
SOURCE_GROUP("engine\\enginesrc\\operating_system\\windows" FILES ${ENGINE_OPERATING_SYSTEM_WINDOWS_SOURCES})
LIST(APPEND ENGINE_SOURCES ${ENGINE_OPERATING_SYSTEM_WINDOWS_SOURCES})

SET(ENGINE_OPERATING_SYSTEM_UNIX_SOURCES
	${ENGINESRC_DIR}/operating_system/unix/unixsystemdirectories.cpp
	${ENGINESRC_DIR}/operating_system/unix/unixsystemdirectories.hpp
	${ENGINESRC_DIR}/operating_system/unix/unixsystemdisplaymanager.cpp
	${ENGINESRC_DIR}/operating_system/unix/unixsystemdisplaymanager.hpp
	${ENGINESRC_DIR}/operating_system/unix/unixsystemwindow.cpp
	${ENGINESRC_DIR}/operating_system/unix/unixsystemwindow.hpp
	${ENGINESRC_DIR}/operating_system/unix/unixsystemmessagebox.hpp
	${ENGINESRC_DIR}/operating_system/unix/unixsysteminfo.cpp
	${ENGINESRC_DIR}/operating_system/unix/unixsysteminfo.hpp
)
SOURCE_GROUP("engine\\enginesrc\\operating_system\\unix" FILES ${ENGINE_OPERATING_SYSTEM_UNIX_SOURCES})
LIST(APPEND ENGINE_SOURCES ${ENGINE_OPERATING_SYSTEM_UNIX_SOURCES})

# System specific files
IF(WIN32)
	SET(ENGINE_SYSTEM_LIBRARIES
	)
	LIST(APPEND ENGINE_DEFINITIONS "-DWINDOWS")
	LIST(APPEND ENGINE_DEFINITIONS "-DOPENGL")
	LIST(APPEND ENGINE_DEFINITIONS "-DDIRECTX")
ENDIF(WIN32)

IF(UNIX)
	SET(ENGINE_SYSTEM_LIBRARIES
		X11
		GL
	)
	LIST(APPEND ENGINE_DEFINITIONS "-DUNIX")
	LIST(APPEND ENGINE_DEFINITIONS "-DOPENGL")
ENDIF(UNIX)

FIND_PACKAGE(Boost 1.36.0 COMPONENTS thread signals date_time REQUIRED)
FIND_PACKAGE(OIS)

LIST(APPEND ENGINE_DEFINITIONS "-D_UNICODE")
LIST(APPEND ENGINE_DEFINITIONS "-DUNICODE")
LIST(APPEND ENGINE_DEFINITIONS "-DCOMPANY_NAME=\"${COMPANY_NAME}\"")
LIST(APPEND ENGINE_DEFINITIONS "-DGAME_NAME=\"${BINARY_NAME}\"")
LIST(APPEND ENGINE_INCLUDE_DIR ${ENGINESRC_DIR})
LIST(APPEND ENGINE_INCLUDE_DIR ${OIS_INCLUDE_DIR})
LIST(APPEND ENGINE_INCLUDE_DIR ${Boost_INCLUDE_DIR})
LIST(APPEND ENGINE_LIBRARIES ${OIS_LIBRARIES})
LIST(APPEND ENGINE_LIBRARIES ${Boost_LIBRARIES})
LIST(APPEND ENGINE_LIBRARIES ${ENGINE_SYSTEM_LIBRARIES})
LIST(APPEND ENGINE_LIBRARY_DIR ${Boost_LIBRARY_DIRS})

SET(ENGINE_DEFINITIONS ${ENGINE_DEFINITIONS} CACHE INTERNAL "")
SET(ENGINE_INCLUDE_DIR ${ENGINE_INCLUDE_DIR} CACHE INTERNAL "")
SET(ENGINE_SOURCES ${ENGINE_SOURCES} CACHE INTERNAL "")
SET(ENGINE_LIBRARIES ${ENGINE_LIBRARIES} CACHE INTERNAL "")

# EOF
