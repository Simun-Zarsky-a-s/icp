//
// Created by samuel on 19.4.2023.
//

#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

Player::Player():
        QGraphicsPixmapItem(),

}

void Player::KeyPressEvent(QKeyEvent * event) {
    qDebug() << "PRESSED";
}
