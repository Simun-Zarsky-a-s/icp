cmake_minimum_required(VERSION 3.23)
project(icp)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(icp main.cpp matrix.cpp matrix.hpp player.h player.cpp welcomeWin.cpp game_view.h)
target_link_libraries(icp Qt5::Widgets)
