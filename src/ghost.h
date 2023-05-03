/**
    * Project: ICP 2022/23
    *
    * @brief Implementation of resource handling
    * @file ghost.h
    *  @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
    */

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include <QGraphicsItem>
#include <QTimer>
#include "player.h"

/**
 * Class representing an object of ghost in the game
 */
class Ghost: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT;

public:
    /**
     * Constructor of ghost
     */
    explicit Ghost(Player*);
    QPoint current_position; //! current position in the map
    void move_ghost(QPoint);
    QTimer ghost_timer;
    int ghost_order;
    void get_next_direction(QPoint target, bool change);
    QPoint get_next_position();
    void change_pixmap();
    bool change = false;

    Sources::Directions direction;
    Sources::Directions previous_direction;
    Sources::Directions s_direction;
    Sources::Directions curr_pixmap;
    void teleport(QPoint position);

private:

    void loadpixmap();

    QPixmap ghost_right_pixmap;
    QPixmap ghost_left_pixmap;
    std::vector<std::vector <QPoint>> Walls;

};


#endif //PACMAN_GHOST_H
