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

    /**
     * Manages movement of all ghosts
     * @param player_position current position of the player
     */
    void move_ghost(QPoint player_position);

    /**
     * Based on current position of the player the ghost towards the player
     * @param target current position of the player
     * @param change flag to change movement strategy
     */
    void get_next_direction(QPoint target, bool change);

    /**
     * Based on direction returns next position of ghost
     * @return next postion of the ghost
     */
    QPoint get_next_position();

    /**
   * Changes orientation of ghost picture based on his direction
   */
    void change_pixmap();

    /**
     * Moves directly the ghost to the position specified by the parameter
     * @param position where to move the ghost
     */
    void teleport(QPoint position);

    QPoint current_position; //! current position in the map
    QTimer ghost_timer; //! timer for ghost
    int ghost_order; //! ghost identifier
    bool change = false; //! flag for changing movement strategy
    Sources::Directions direction; //! direction of movement
    Sources::Directions curr_pixmap; //! picture in the scene


private:
    /**
     * Loads a picture to be placed in the map
     */
    void loadpixmap();

    QPixmap ghost_right_pixmap; //! pixmap for for ghost when heading right
    QPixmap ghost_left_pixmap; //! pixmap for for ghost when heading left
    std::vector<std::vector <QPoint>> Walls; //! vector containing wall for intersection check

};


#endif //PACMAN_GHOST_H
