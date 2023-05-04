# Pacman.pro

# Minimum required version of Qt
QT += core gui widgets

# Target
TARGET = pacman

# Source files
SOURCES += game.cpp game_scene.cpp game_view.cpp ghost.cpp logger.cpp main.cpp resources.cpp player.cpp welcomeWin.cpp Sources.cpp

# Header files
HEADERS += game_scene.h game_view.h ghost.h logger.h resources.hpp player.h welcomeWin.h Sources.h

# Resource files
RESOURCES += resources.qrc

# Compile flags
CONFIG += c++17

# Include directories
INCLUDEPATH += .

# Linker flags
LIBS += -lQt5Core -lQt5Gui -lQt5Widgets

# Output directory
DESTDIR = ../build/

# Object directory
OBJECTS_DIR = ../build/obj/

# MOC header files
HEADERS_MOC += game_scene.h game_view.h ghost.h logger.h player.h welcomeWin.h

# Rules
QMAKE_CXXFLAGS += -Wall

# Installation target
target.path = /usr/local/bin


