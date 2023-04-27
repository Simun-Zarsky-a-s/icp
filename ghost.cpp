//
// Created by samuel on 25.4.2023.
//

#include "ghost.h"
#include "Sources.h"
#include <QGraphicsPixmapItem>
#include <QDebug>


Ghost::Ghost(Player* game_player) : QGraphicsPixmapItem(), direction(NONE), curr_pixmap(RIGHT) {
    loadpixmap();
    player = game_player;
    setPixmap(ghost_right_pixmap);
    setTransformOriginPoint(Sources::size, Sources::size);
    connect(&ghost_timer, &QTimer::timeout, this, &Ghost::loop);
    ghost_timer.start(Sources::FPS);
}

void Ghost::loop() {

}

void Ghost::loadpixmap() {
    ghost_right_pixmap = QPixmap(Sources::Ghost_file_destination).scaled(Sources::size, Sources::size, Qt::KeepAspectRatio);
    ghost_left_pixmap = ghost_right_pixmap.transformed(QTransform().scale(-1,1));
}

void Ghost::move_ghost(QPoint location) {
    setPos(location);
    current_position = location;
}

void Ghost::change_pixmap(){
    if (curr_pixmap == RIGHT && direction == LEFT)
        setPixmap(ghost_left_pixmap);
    else if (curr_pixmap == LEFT && direction == RIGHT)
        setPixmap(ghost_right_pixmap);
}
