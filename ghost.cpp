//
// Created by samuel on 25.4.2023.
//

#include "ghost.h"
#include "Sources.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

Ghost::Ghost() : QGraphicsPixmapItem() {
    loadpixmap();
    setPixmap(ghost_right_pixmap);
    setTransformOriginPoint(Sources::size, Sources::size);
    qDebug() << "HEREE";
}

void Ghost::loadpixmap() {
    ghost_right_pixmap = QPixmap(Sources::Ghost_file_destination).scaled(Sources::size, Sources::size, Qt::KeepAspectRatio);
    ghost_left_pixmap = ghost_right_pixmap.transformed(QTransform().scale(-1,1));
}
