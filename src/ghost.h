/**
    * Project: ICP 2022/23
    *
    * @brief Implementation of resource handling
    * @file ghost.h
    * @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
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
     * @brief Constructor of ghost
     */
    explicit Ghost(Player*);

    /**
     * @brief Manages movement of all ghosts
     * @param player_position current position of the player
     */
    void move_ghost(QPoint player_position);

    /**
     * @brief Based on current position of the player the ghost towards the player
     * @param target current position of the player
     * @param change flag to change movement strategy
     */
    void get_next_direction(QPoint target, bool change);

    /**
     * @brief Based on direction returns next position of ghost
     * @return next postion of the ghost
     */
    QPoint get_next_position();

    /**
   * @brief Changes orientation of ghost picture based on his direction
   */
    void change_pixmap();

    /**
     * @brief Moves directly the ghost to the position specified by the parameter
     * @param position where to move the ghost
     */
    void teleport(QPoint position);


    //! current position in the map
    QPoint current_position;

    //! timer for ghost
    QTimer ghost_timer;

    //! ghost identifier
    int ghost_order;

    //! flag for changing movement strategy
    bool change = false;

    //! direction of movement
    Sources::Directions direction;

    //! picture in the scene
    Sources::Directions curr_pixmap;


private:
    /**
     * @brief Loads a picture to be placed in the map
     */
    void loadpixmap();

    //! pixmap for for ghost when heading right
    QPixmap ghost_right_pixmap;

    //! pixmap for for ghost when heading left
    QPixmap ghost_left_pixmap;

    //! vector containing wall for intersection check
    std::vector<std::vector <QPoint>> Walls;

};


#endif //PACMAN_GHOST_H
