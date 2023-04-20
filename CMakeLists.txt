cmake_minimum_required(VERSION 3.23)
project(icp)

set(CMAKE_PREFIX_PATH "/home/daniel/Qt/Tools/QtDesignStudio/qt5_design_studio_reduced_version/lib/cmake/")
find_package(Qt5Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(icp main.cpp matrix.cpp matrix.hpp welcomeWin.cpp)
target_link_libraries(icp Qt5::Widgets)
