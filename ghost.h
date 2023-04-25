//
// Created by samuel on 25.4.2023.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include <QGraphicsItem>


class Ghost: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT;

public:
    explicit Ghost(std::vector<std::vector <QPoint>> Walls_cur);
    QPoint current_position;

private:
    std::vector<std::vector <QPoint>> Walls;



};


#endif //PACMAN_GHOST_H
