CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(SOURCES
	enginesrc/main.cpp
	enginesrc/debug.cpp
	enginesrc/engine.cpp
	enginesrc/time.cpp
	enginesrc/functionmanager.cpp
	enginesrc/scene/scenemanager.cpp
)
#SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_scripts)
#INCLUDE(MathModule)
FIND_PACKAGE(wxWidgets COMPONENTS base core REQUIRED)
INCLUDE(${wxWidgets_USE_FILE})
FIND_PACKAGE(Boost 1.35.0 COMPONENTS thread signals date_time REQUIRED)

ADD_DEFINITIONS(${DEFINITIONS})
INCLUDE_DIRECTORIES(include ${wxWidgets_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
ADD_EXECUTABLE(engine WIN32 ${SOURCES})
TARGET_LINK_LIBRARIES(engine ${wxWidgets_LIBRARIES} ${Boost_LIBRARIES})

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
	ADD_CUSTOM_TARGET(docs ${DOXYGEN_EXECUTABLE} doxygen.conf WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMENT "Generating documentation")
ELSE(DOXYGEN_FOUND)
	ADD_CUSTOM_TARGET(docs COMMENT "Doxygen not found.")
ENDIF(DOXYGEN_FOUND)

