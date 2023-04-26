//
// Created by samuel on 25.4.2023.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include <QGraphicsItem>


class Ghost: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT;

public:
    explicit Ghost();
    QPoint current_position;

private:
    void loadpixmap();

    QPixmap ghost_right_pixmap;
    QPixmap ghost_left_pixmap;

    std::vector<std::vector <QPoint>> Walls;



};


#endif //PACMAN_GHOST_H
