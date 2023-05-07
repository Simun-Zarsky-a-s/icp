/**
    * Project: ICP 2022/23
    *
    * @brief Implementation of ghost
    * @file ghost.cpp
    *  @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
    */


#include "ghost.h"
#include "Sources.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

Ghost::Ghost() : QGraphicsPixmapItem() {
    loadpixmap();

    setPixmap(ghost_right_pixmap);
    setTransformOriginPoint(Sources::size, Sources::size);
    setFlag(ItemIsFocusable);
}

void Ghost::teleport(QPoint position) {
    setPos(position);
    current_position = position;
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
