//
// Created by samuel on 25.4.2023.
//

#include "ghost.h"

Ghost::Ghost(std::vector<std::vector <QPoint>> Walls_cur) : QGraphicsPixmapItem() {
    Walls = Walls_cur;

}
