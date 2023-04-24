//
// Created by samuel on 20.4.2023.
//

#ifndef PACMAN_SOURCES_H
#define PACMAN_SOURCES_H
#include <QPoint>
#include <vector>


class Sources {
public:
    Sources();

    constexpr static QPoint RT_PACMAN_UP = QPoint(90, 0);
    constexpr const static QPoint RT_PACMAN_DOWN = QPoint(-90,0);
    constexpr const static QPoint RT_PACMAN_LEFT = QPoint(0,90);
    constexpr const static QPoint RT_PACMAN_RIGHT = QPoint(0,0);

    const static int size = 40;

    const static std::vector<std::vector <char>> Map;
};

#endif //PACMAN_SOURCES_H
