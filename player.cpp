//
// Created by samuel on 19.4.2023.
//

#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include "Sources.h"
#include "game_scene.h"
#include <random>



Player::Player():
    QGraphicsPixmapItem(), alive(true)
{
    load_player_pixmap();
    /// Default direction of player
    setPixmap(pix_map_player_right);
    setTransformOriginPoint(Sources::size, Sources::size);
    setFlag(ItemIsFocusable);
}

void Player::load_player_pixmap() {
    pix_map_player_right = QPixmap(Sources::Player_file_destination);
    pix_map_player_right = pix_map_player_right.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio);

    qreal rRadius = pix_map_player_right.width() / 2;

    pix_map_player_up = pix_map_player_right.transformed(
            QTransform().translate(-rRadius, -rRadius).rotate(-90).translate(rRadius, rRadius));
    pix_map_player_down = pix_map_player_right.transformed(
            QTransform().translate(-rRadius, -rRadius).rotate(90).translate(rRadius, rRadius));
    pix_map_player_left = pix_map_player_right.transformed(
            QTransform().scale(-1,1));
}

void Player::update_player_pixmap() {
    switch (direction) {
        case Sources::UP:
            setPixmap(pix_map_player_up);
            break;
        case Sources::DOWN:
            setPixmap(pix_map_player_down);
            break;
        case Sources::RIGHT:
            setPixmap(pix_map_player_right);
            break;
        case Sources::LEFT:
            setPixmap(pix_map_player_left);
            break;
        case Sources::NONE:
            break;
    }
}

QPoint Player::next_player_position() const {
    switch (direction) {
        case Sources::UP:
            return {current_position.x(), current_position.y() - Sources::size/Sources::SWIFT};
        case Sources::DOWN:
            return  {current_position.x(), current_position.y() + Sources::size/Sources::SWIFT};
        case Sources::RIGHT:
            return {current_position.x() + Sources::size/Sources::SWIFT, current_position.y()};
        case Sources::LEFT:
            return {current_position.x() - Sources::size/Sources::SWIFT, current_position.y()};
        case Sources::NONE:
            return {current_position.x(), current_position.y()};
    }
    return {0,0};
}

void Player::teleport_player(QPoint location) {
    setPos(location);
    current_position = location;
}

void Player::control_player_mouse() {
    qDebug() << current_position << " " << mouse_target;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, 1);

    if (!wall_dmg){
        if (!(current_position.x() > mouse_target.x() - Sources::size && current_position.x() < mouse_target.x() + Sources::size)) {
            if (current_position.x() < mouse_target.x())
                direction = Sources::RIGHT;
            else if (current_position.x() > mouse_target.x())
                direction = Sources::LEFT;
        }
        else{
            if (current_position.y() > mouse_target.y() - Sources::size && current_position.y() < mouse_target.y() + Sources::size)
                direction = Sources::NONE;
            else if (current_position.y() < mouse_target.y())
                direction = Sources::DOWN;
            else if (current_position.y() > mouse_target.y())
                direction = Sources::UP;
        }
    }
    else {
        int roll = distr(eng);
        if (direction == Sources::UP || direction == Sources::DOWN){
            if (roll == 0)
                direction = Sources::RIGHT;
            else
                direction = Sources::LEFT;

        }
        else if (direction == Sources::LEFT || direction == Sources::RIGHT){
            if (current_position.y() > mouse_target.y() - Sources::size && current_position.y() < mouse_target.y() + Sources::size)
                if (roll == 0)
                    direction = Sources::UP;
                else
                    direction = Sources::DOWN;
            else if (current_position.y() < mouse_target.y())
                direction = Sources::DOWN;
            else if (current_position.y() > mouse_target.y())
                direction = Sources::UP;
        }
    }
}
