//
// Created by samuel on 19.4.2023.
//

#ifndef ICP_PLAYER_H
#define ICP_PLAYER_H


#include <QGraphicsItem>
#include <QTimer>
#include "Sources.h"
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>


class Player: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Player();
    QPoint next_player_position() const;
    void teleport_player(QPoint);
    QPoint current_position;
    enum Directions{UP,DOWN,LEFT,RIGHT, NONE};
    Directions direction = NONE;
    Directions previous_direction = NONE;
    bool alive;
    void update_player_pixmap();
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


private:
    void load_player_pixmap();
    void keyPressEvent(QKeyEvent *event) override;

    QPixmap pix_map_player_up ;
    QPixmap pix_map_player_down;
    QPixmap pix_map_player_right;
    QPixmap pix_map_player_left;

};

#endif //ICP_PLAYER_H