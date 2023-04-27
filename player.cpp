//
// Created by samuel on 19.4.2023.
//

#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include "Sources.h"



Player::Player():
        QGraphicsPixmapItem(), alive(true)
{
    load_player_pixmap();
    /// Default direction of player
    setPixmap(pix_map_player_right);
    setTransformOriginPoint(Sources::size, Sources::size);
    setFlag(ItemIsFocusable); // Neviem preco ale musi to tu byt
}

void Player::load_player_pixmap() {
    pix_map_player_right = QPixmap(":/content/pacman.png");
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
        case UP:
            setPixmap(pix_map_player_up);
            break;
        case DOWN:
            setPixmap(pix_map_player_down);
            break;
        case RIGHT:
            setPixmap(pix_map_player_right);
            break;
        case LEFT:
            setPixmap(pix_map_player_left);
            break;
        case NONE:
            break;
    }
}

QPoint Player::next_player_position() const {
    switch (direction) {
        case UP:
            return {current_position.x(), current_position.y() - Sources::size/Sources::SWIFT};
        case DOWN:
            return  {current_position.x(), current_position.y() + Sources::size/Sources::SWIFT};
        case RIGHT:
            return {current_position.x() + Sources::size/Sources::SWIFT, current_position.y()};
        case LEFT:
            return {current_position.x() - Sources::size/Sources::SWIFT, current_position.y()};
        case NONE:
            return {current_position.x(), current_position.y()};
    }
    return {0,0};
}

void Player::teleport_player(QPoint location) {
    setPos(location);
    current_position = location;
}


void Player::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
        case Qt::Key_Up:
            direction = UP;
            break;
        case Qt::Key_Down:
            direction = DOWN;
            break;
        case Qt::Key_Right:
            direction = RIGHT;
            break;
        case Qt::Key_Left:
            direction = LEFT;
            break;
        default:
            break;
    }
    QGraphicsPixmapItem::keyPressEvent(event);
}
