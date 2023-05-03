cmake_minimum_required(VERSION 3.23)
project(icp)
find_package(Qt5Widgets REQUIRED)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

add_executable(icp
        src/main.cpp
        src/resources.cpp
        src/resources.hpp
        src/logger.h
        src/logger.cpp
        src/player.h
        src/player.cpp
        src/game_view.cpp
        src/welcomeWin.cpp
        src/game_view.h
        src/Sources.cpp
        src/game_scene.cpp
        src/resources.qrc
        src/ghost.cpp
        )

target_link_libraries(icp Qt5::Widgets)

option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/src/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)