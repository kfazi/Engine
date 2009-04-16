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
	${ENGINESRC_DIR}/sqliteconfig.cpp
	${ENGINESRC_DIR}/sqliteconfig.hpp
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

SET(ENGINE_3RDPARTY_SQLITE_SOURCES
	${ENGINESRC_DIR}/3rdparty/sqlite/alter.c
	${ENGINESRC_DIR}/3rdparty/sqlite/analyze.c
	${ENGINESRC_DIR}/3rdparty/sqlite/attach.c
	${ENGINESRC_DIR}/3rdparty/sqlite/auth.c
	${ENGINESRC_DIR}/3rdparty/sqlite/backup.c
	${ENGINESRC_DIR}/3rdparty/sqlite/bitvec.c
	${ENGINESRC_DIR}/3rdparty/sqlite/btmutex.c
	${ENGINESRC_DIR}/3rdparty/sqlite/btree.c
	${ENGINESRC_DIR}/3rdparty/sqlite/btree.h
	${ENGINESRC_DIR}/3rdparty/sqlite/btreeInt.h
	${ENGINESRC_DIR}/3rdparty/sqlite/build.c
	${ENGINESRC_DIR}/3rdparty/sqlite/callback.c
	${ENGINESRC_DIR}/3rdparty/sqlite/complete.c
	${ENGINESRC_DIR}/3rdparty/sqlite/date.c
	${ENGINESRC_DIR}/3rdparty/sqlite/delete.c
	${ENGINESRC_DIR}/3rdparty/sqlite/expr.c
	${ENGINESRC_DIR}/3rdparty/sqlite/fault.c
	${ENGINESRC_DIR}/3rdparty/sqlite/fts3.c
	${ENGINESRC_DIR}/3rdparty/sqlite/fts3.h
	${ENGINESRC_DIR}/3rdparty/sqlite/fts3_expr.c
	${ENGINESRC_DIR}/3rdparty/sqlite/fts3_expr.h
	${ENGINESRC_DIR}/3rdparty/sqlite/fts3_hash.c
	${ENGINESRC_DIR}/3rdparty/sqlite/fts3_hash.h
	${ENGINESRC_DIR}/3rdparty/sqlite/fts3_icu.c
	${ENGINESRC_DIR}/3rdparty/sqlite/fts3_porter.c
	${ENGINESRC_DIR}/3rdparty/sqlite/fts3_tokenizer.c
	${ENGINESRC_DIR}/3rdparty/sqlite/fts3_tokenizer.h
	${ENGINESRC_DIR}/3rdparty/sqlite/fts3_tokenizer1.c
	${ENGINESRC_DIR}/3rdparty/sqlite/func.c
	${ENGINESRC_DIR}/3rdparty/sqlite/global.c
	${ENGINESRC_DIR}/3rdparty/sqlite/hash.c
	${ENGINESRC_DIR}/3rdparty/sqlite/hash.h
	${ENGINESRC_DIR}/3rdparty/sqlite/hwtime.h
	${ENGINESRC_DIR}/3rdparty/sqlite/insert.c
	${ENGINESRC_DIR}/3rdparty/sqlite/journal.c
	${ENGINESRC_DIR}/3rdparty/sqlite/keywordhash.h
	${ENGINESRC_DIR}/3rdparty/sqlite/legacy.c
	${ENGINESRC_DIR}/3rdparty/sqlite/loadext.c
	${ENGINESRC_DIR}/3rdparty/sqlite/main.c
	${ENGINESRC_DIR}/3rdparty/sqlite/malloc.c
	${ENGINESRC_DIR}/3rdparty/sqlite/mem0.c
	${ENGINESRC_DIR}/3rdparty/sqlite/mem1.c
	${ENGINESRC_DIR}/3rdparty/sqlite/mem2.c
	${ENGINESRC_DIR}/3rdparty/sqlite/mem3.c
	${ENGINESRC_DIR}/3rdparty/sqlite/mem5.c
	${ENGINESRC_DIR}/3rdparty/sqlite/memjournal.c
	${ENGINESRC_DIR}/3rdparty/sqlite/mutex.c
	${ENGINESRC_DIR}/3rdparty/sqlite/mutex.h
	${ENGINESRC_DIR}/3rdparty/sqlite/mutex_noop.c
	${ENGINESRC_DIR}/3rdparty/sqlite/mutex_os2.c
	${ENGINESRC_DIR}/3rdparty/sqlite/mutex_unix.c
	${ENGINESRC_DIR}/3rdparty/sqlite/mutex_w32.c
	${ENGINESRC_DIR}/3rdparty/sqlite/notify.c
	${ENGINESRC_DIR}/3rdparty/sqlite/opcodes.c
	${ENGINESRC_DIR}/3rdparty/sqlite/opcodes.h
	${ENGINESRC_DIR}/3rdparty/sqlite/os.c
	${ENGINESRC_DIR}/3rdparty/sqlite/os.h
	${ENGINESRC_DIR}/3rdparty/sqlite/os_common.h
	${ENGINESRC_DIR}/3rdparty/sqlite/os_os2.c
	${ENGINESRC_DIR}/3rdparty/sqlite/os_unix.c
	${ENGINESRC_DIR}/3rdparty/sqlite/os_win.c
	${ENGINESRC_DIR}/3rdparty/sqlite/pager.c
	${ENGINESRC_DIR}/3rdparty/sqlite/pager.h
	${ENGINESRC_DIR}/3rdparty/sqlite/parse.c
	${ENGINESRC_DIR}/3rdparty/sqlite/parse.h
	${ENGINESRC_DIR}/3rdparty/sqlite/pcache.c
	${ENGINESRC_DIR}/3rdparty/sqlite/pcache.h
	${ENGINESRC_DIR}/3rdparty/sqlite/pcache1.c
	${ENGINESRC_DIR}/3rdparty/sqlite/pragma.c
	${ENGINESRC_DIR}/3rdparty/sqlite/prepare.c
	${ENGINESRC_DIR}/3rdparty/sqlite/printf.c
	${ENGINESRC_DIR}/3rdparty/sqlite/random.c
	${ENGINESRC_DIR}/3rdparty/sqlite/resolve.c
	${ENGINESRC_DIR}/3rdparty/sqlite/rowset.c
	${ENGINESRC_DIR}/3rdparty/sqlite/rtree.c
	${ENGINESRC_DIR}/3rdparty/sqlite/rtree.h
	${ENGINESRC_DIR}/3rdparty/sqlite/select.c
	${ENGINESRC_DIR}/3rdparty/sqlite/shell.c
	${ENGINESRC_DIR}/3rdparty/sqlite/sqlite3.h
	${ENGINESRC_DIR}/3rdparty/sqlite/sqlite3ext.h
	${ENGINESRC_DIR}/3rdparty/sqlite/sqliteicu.h
	${ENGINESRC_DIR}/3rdparty/sqlite/sqliteInt.h
	${ENGINESRC_DIR}/3rdparty/sqlite/sqliteLimit.h
	${ENGINESRC_DIR}/3rdparty/sqlite/status.c
	${ENGINESRC_DIR}/3rdparty/sqlite/table.c
	${ENGINESRC_DIR}/3rdparty/sqlite/tokenize.c
	${ENGINESRC_DIR}/3rdparty/sqlite/trigger.c
	${ENGINESRC_DIR}/3rdparty/sqlite/update.c
	${ENGINESRC_DIR}/3rdparty/sqlite/utf.c
	${ENGINESRC_DIR}/3rdparty/sqlite/util.c
	${ENGINESRC_DIR}/3rdparty/sqlite/vacuum.c
	${ENGINESRC_DIR}/3rdparty/sqlite/vdbe.c
	${ENGINESRC_DIR}/3rdparty/sqlite/vdbe.h
	${ENGINESRC_DIR}/3rdparty/sqlite/vdbeapi.c
	${ENGINESRC_DIR}/3rdparty/sqlite/vdbeaux.c
	${ENGINESRC_DIR}/3rdparty/sqlite/vdbeblob.c
	${ENGINESRC_DIR}/3rdparty/sqlite/vdbeInt.h
	${ENGINESRC_DIR}/3rdparty/sqlite/vdbemem.c
	${ENGINESRC_DIR}/3rdparty/sqlite/vtab.c
	${ENGINESRC_DIR}/3rdparty/sqlite/walker.c
	${ENGINESRC_DIR}/3rdparty/sqlite/where.c
)
SOURCE_GROUP("engine\\enginesrc\\3rdparty\\sqlite" FILES ${ENGINE_3RDPARTY_SQLITE_SOURCES})
LIST(APPEND ENGINE_SOURCES ${ENGINE_3RDPARTY_SQLITE_SOURCES})

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
