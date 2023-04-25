//
// Created by samuel on 20.4.2023.
//

#ifndef PACMAN_SOURCES_H
#define PACMAN_SOURCES_H
#include <QPoint>
#include <vector>
#include <QObject>


class Sources {
public:
    Sources();

    const static int size = 60;
    const static int FPS = 300;

    const static int MAP_WIDTH = 6;
    const static int MAP_HEIGHT = 6;

    QObject target;
    std::vector<QObject> Walls;
    std::vector<QObject> Grass;
    std::vector<QObject> Keys;

    const static std::vector<std::vector <char>> Map;
};

#endif //PACMAN_SOURCES_H
