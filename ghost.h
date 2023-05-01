//
// Created by samuel on 25.4.2023.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include <QGraphicsItem>
#include <QTimer>
#include "player.h"
#include "logger.h"


class Ghost: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT;

public:
    explicit Ghost(Player*, Logger*);
    QPoint current_position;
    void move_ghost(QPoint);
    QTimer ghost_timer;
    int ghost_order;
    void get_next_direction(QPoint target, bool change);
    QPoint get_next_position();
    void change_pixmap();
    bool change = false;

    enum Directions{UP,DOWN,LEFT,RIGHT, NONE};
    Directions direction;
    Directions previous_direction;
    Directions s_direction;
    Directions curr_pixmap;

private:
    void loadpixmap();

    void loop();



    QPixmap ghost_right_pixmap;
    QPixmap ghost_left_pixmap;
    Player* player;
    std::vector<std::vector <QPoint>> Walls;



};


#endif //PACMAN_GHOST_H
