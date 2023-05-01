//
// Created by samuel on 25.4.2023.
//

#include "ghost.h"
#include "Sources.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include "logger.h"


Ghost::Ghost(Player* game_player, Logger* logger) : QGraphicsPixmapItem() {
    loadpixmap();
    player = game_player;
    setPixmap(ghost_right_pixmap);
    previous_direction = NONE;
    setTransformOriginPoint(Sources::size, Sources::size);
    if (!Sources::play_log_mode) {
        connect(&ghost_timer, &QTimer::timeout, this, &Ghost::loop);
        ghost_timer.start(Sources::FPS);
    }
    setFlag(ItemIsFocusable);
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

void Ghost::get_next_direction(QPoint target){
    if(current_position.x() < target.x() ){
        direction = RIGHT;

    }
    else if (current_position.x() > target.x()){
        direction = LEFT;

    }
    else{
        if(current_position.y() < target.y()){
            direction = UP;

        }
        else if(current_position.y() > target.y()){
            direction = DOWN;

        }
        else{
            direction = NONE;

        }
    }
}

QPoint Ghost::get_next_position(){
    switch (direction) {
        case UP:
            return {current_position.x(), current_position.y() + Sources::size/Sources::GHOST_SWIFT};
        case DOWN:
            return  {current_position.x(), current_position.y() - Sources::size/Sources::GHOST_SWIFT};
        case RIGHT:
            return {current_position.x() + Sources::size/Sources::GHOST_SWIFT, current_position.y()};
        case LEFT:
            return {current_position.x() - Sources::size/Sources::GHOST_SWIFT, current_position.y()};
        case NONE:
            return {current_position.x(), current_position.y()};
    }
    return {0,0};
}
