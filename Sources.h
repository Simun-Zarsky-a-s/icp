//
// Created by samuel on 20.4.2023.
//

#ifndef PACMAN_SOURCES_H
#define PACMAN_SOURCES_H

#include <QPoint>
#include <vector>
#include <QObject>
#include <QPixmap>
#include <QString>


class Sources {
public:
    const static int size = 60;
    const static int FPS = 100;

     static int MAP_WIDTH;
     static int MAP_HEIGHT;

    const static int SWIFT = 32;
    const static int GHOST_SWIFT = 32;
    static bool play_log_mode;

    enum Directions{UP,DOWN,LEFT,RIGHT, NONE};

    static QString Wall_file_destination;
    static QString Grass_file_destination;
    static QString Player_file_destination;
    static QString Door_closed_file_destination;
    static QString Door_open_file_destination;
    static QString Key_file_destination;
    static QString Ghost_file_destination;
    static QString Map_file_destination;

    QObject target;
    std::vector<QObject> Walls;
    std::vector<QObject> Grass;
    std::vector<QObject> Keys;

    static std::string log_file;

    const static std::vector<std::vector <char>> Map;
    static std::vector<std::vector <char>> Matrix;
};




#endif //PACMAN_SOURCES_H
