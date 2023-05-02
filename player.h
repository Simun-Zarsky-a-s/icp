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
    [[nodiscard]] QPoint next_player_position() const;
    QPoint mouse_target;
    void teleport_player(QPoint);
    QPoint current_position;
    Sources::Directions direction = Sources::NONE;
    Sources::Directions previous_direction = Sources::NONE;
    bool alive;
    bool wall_dmg = false;
    bool mouse_mode = false;
    void update_player_pixmap();
    void control_player_mouse();
    QGraphicsPixmapItem* scene_map[100][100]{} ;



private:
    void load_player_pixmap();

    QPixmap pix_map_player_up ;
    QPixmap pix_map_player_down;
    QPixmap pix_map_player_right;
    QPixmap pix_map_player_left;

};

#endif //ICP_PLAYER_H