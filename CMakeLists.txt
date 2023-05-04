cmake_minimum_required(VERSION 3.23)
project(pacman)
find_package(Qt5Widgets REQUIRED)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

list (APPEND RESOURCES src/resources.qrc)
qt5_add_resources(RCC_SOURCES ${RESOURCES})

add_executable(pacman
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
        src/ghost.cpp
        ${RCC_SOURCES}
        )

include_directories(
        ${CMAKE_SOURCE_DIR}/content
        ${CMAKE_SOURCE_DIR}/examples
)

target_link_libraries(pacman Qt5::Core Qt5::Widgets)
