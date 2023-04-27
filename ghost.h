//
// Created by samuel on 25.4.2023.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include <QGraphicsItem>
#include <QTimer>
#include "player.h"


class Ghost: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT;

public:
    explicit Ghost(Player*);
    QPoint current_position;
    void move_ghost(QPoint);
    QTimer ghost_timer;

private:
    void loadpixmap();
    void change_pixmap();
    void loop();


    QPixmap ghost_right_pixmap;
    QPixmap ghost_left_pixmap;
    Player* player;


    enum Directions{UP,DOWN,LEFT,RIGHT, NONE};
    Directions direction;
    Directions curr_pixmap;

    std::vector<std::vector <QPoint>> Walls;



};


#endif //PACMAN_GHOST_H
