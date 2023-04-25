cmake_minimum_required(VERSION 3.23)
project(icp)
find_package(Qt5Widgets REQUIRED)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

add_executable(icp main.cpp matrix.cpp matrix.hpp player.h player.cpp game_view.cpp welcomeWin.cpp game_view.h Sources.cpp game_scene.cpp)
target_link_libraries(icp Qt5::Widgets)
