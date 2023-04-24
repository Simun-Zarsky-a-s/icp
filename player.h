//
// Created by samuel on 19.4.2023.
//

#ifndef ICP_PLAYER_H
#define ICP_PLAYER_H

#endif //ICP_PLAYER_H

#include <QGraphicsItem>
#include <QTimer>
#include "Sources.h"



class Player: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    explicit Player();

private:
    void update_player();
    void key_pressed(QKeyEvent *event);
    void takeKey();
    int getKeys();

    QPixmap pix_map_player_up ;
    QPixmap pix_map_player_down;
    QPixmap pix_map_player_right;
    QPixmap pix_map_player_left;
    QPixmap pix_player;
    enum Directions{UP,DOWN,LEFT,RIGHT};
    std::vector<Directions> directions;
    int taken_keys = 0;

    QTimer timer;
};