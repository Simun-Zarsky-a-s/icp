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
    int ghost_order;
    void get_next_direction(QPoint target, bool change);
    QPoint get_next_position();
    void change_pixmap();
    bool change = false;

    Sources::Directions direction;
    Sources::Directions previous_direction;
    Sources::Directions s_direction;
    Sources::Directions curr_pixmap;
    void teleport(QPoint position);

private:
    void loadpixmap();

    void loop();



    QPixmap ghost_right_pixmap;
    QPixmap ghost_left_pixmap;
    Player* player;
    std::vector<std::vector <QPoint>> Walls;



};


#endif //PACMAN_GHOST_H
