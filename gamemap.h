//
// Created by samuel on 24.4.2023.
//

#ifndef PACMAN_GAMEMAP_H
#define PACMAN_GAMEMAP_H

#include <QObject>

class Player;


class Gamemap {
    Q_OBJECT;

public:
    explicit Gamemap();

    static int MAP_WIDTH;
    static int MAP_HEIGHT;

    QObject target;
    std::vector<QObject> Walls;
    std::vector<QObject> Grass;
    std::vector<QObject> Keys;

};


#endif //PACMAN_GAMEMAP_H
