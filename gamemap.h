//
// Created by samuel on 24.4.2023.
//

#ifndef PACMAN_GAMEMAP_H
#define PACMAN_GAMEMAP_H

#include <QObject>
#include "Sources.h"

class Player;


class Gamemap {
    Q_OBJECT;

public:
    explicit Gamemap();

    const static int MAP_WIDTH = 4;
    const static int MAP_HEIGHT = 4;

    QObject target;
    std::vector<QObject> Walls;
    std::vector<QObject> Grass;
    std::vector<QObject> Keys;

};


#endif //PACMAN_GAMEMAP_H
