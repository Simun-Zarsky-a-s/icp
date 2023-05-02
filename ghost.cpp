//
// Created by samuel on 25.4.2023.
//

#include "ghost.h"
#include "Sources.h"
#include <QGraphicsPixmapItem>
#include <QDebug>


Ghost::Ghost(Player* game_player) : QGraphicsPixmapItem() {
    loadpixmap();
    player = game_player;
    setPixmap(ghost_right_pixmap);
    previous_direction = Sources::NONE;
    setTransformOriginPoint(Sources::size, Sources::size);
    if (!Sources::play_log_mode) {
        connect(&ghost_timer, &QTimer::timeout, this, &Ghost::loop);
        ghost_timer.start(Sources::FPS);
    }
    setFlag(ItemIsFocusable);
}

void Ghost::loop() {

}

void Ghost::teleport(QPoint position) {
    setPos(position);
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
    if (curr_pixmap == Sources::RIGHT && direction == Sources::LEFT)
        setPixmap(ghost_left_pixmap);
    else if (curr_pixmap == Sources::LEFT && direction == Sources::RIGHT)
        setPixmap(ghost_right_pixmap);
}

void Ghost::get_next_direction(QPoint target, bool change){
    if (!change){
        if(current_position.x() < target.x()){
            direction = Sources::RIGHT;
        }
        else if (current_position.x() > target.x()){
            direction = Sources::LEFT;
        }
        else{
            if(current_position.y() < target.y()){
                direction = Sources::UP;
            }
            else if(current_position.y() > target.y()){
                direction = Sources::DOWN;
            }
            else{
                direction = Sources::NONE;
            }
        }
    }
    else{
        if(current_position.y() < target.y()){
            direction = Sources::UP;
        }
        else if (current_position.y() > target.y()){
            direction = Sources::DOWN;
        }
        else{
            if(current_position.x() < target.x()){
                direction = Sources::RIGHT;
            }
            else if(current_position.x() > target.x()){
                direction = Sources::LEFT;
            }
            else{
                direction = Sources::NONE;
            }
        }
    }

}

QPoint Ghost::get_next_position(){
    switch (direction) {
        case Sources::UP:
            return {current_position.x(), current_position.y() + Sources::size/Sources::GHOST_SWIFT};
        case Sources::DOWN:
            return  {current_position.x(), current_position.y() - Sources::size/Sources::GHOST_SWIFT};
        case Sources::RIGHT:
            return {current_position.x() + Sources::size/Sources::GHOST_SWIFT, current_position.y()};
        case Sources::LEFT:
            return {current_position.x() - Sources::size/Sources::GHOST_SWIFT, current_position.y()};
        case Sources::NONE:
            return {current_position.x(), current_position.y()};
    }
    return {0,0};
}
