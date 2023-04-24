//
// Created by samuel on 19.4.2023.
//

#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include "Sources.h"

Player::Player():
        QGraphicsPixmapItem()
{
    /// Default direction of player
    setPixmap(Sources::RT_PACMAN_RIGHT.x(), Sources::RT_PACMAN_RIGHT.y(), Sources::size, Sources::size);
    setTransformOriginPoint(Sources::size, Sources::size);
    connect(&timer, &QTimer::timeout, this, &Player::update_player);

}

void Player::update_player(){
    switch (directions.front()) {
        case UP:
            setPixmap(Sources::RT_PACMAN_UP.x(), Sources::RT_PACMAN_UP.y(), Sources::size, Sources::size);
        case DOWN:
            setPixmap(Sources::RT_PACMAN_DOWN.x(), Sources::RT_PACMAN_DOWN.y(), Sources::size, Sources::size);
        case RIGHT:
            setPixmap(Sources::RT_PACMAN_RIGHT.x(), Sources::RT_PACMAN_RIGHT.y(), Sources::size, Sources::size);
        case LEFT:
            setPixmap(Sources::RT_PACMAN_LEFT.x(), Sources::RT_PACMAN_LEFT.y(), Sources::size, Sources::size);
    }
}


void Player::key_pressed(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            directions.insert(directions.begin(), UP);
        case Qt::Key_Down:
            directions.insert(directions.begin(), DOWN);
        case Qt::Key_Right:
            directions.insert(directions.begin(), RIGHT);
        case Qt::Key_Left:
            directions.insert(directions.begin(), LEFT);
        default:
            break;
    }
}

void Player::takeKey() {
    taken_keys++;
}

int Player::getKeys() {
    return taken_keys;
}

