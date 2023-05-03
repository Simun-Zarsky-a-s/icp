/**
 * @file player.h
 * @section Player
 * @brief Library for player
 * @name Player
 * @date 20.4.2023
 */

#ifndef ICP_PLAYER_H
#define ICP_PLAYER_H


#include <QGraphicsItem>
#include <QTimer>
#include "Sources.h"
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>


/**
 * @brief The Player class represents a player object that is displayed as a pixmap item in a QGraphicsScene.
 * @brief This class inherits from QObject and QGraphicsPixmapItem.
 * @author Samuel Šimún
 * @date 24.4.2023
 */
class Player: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    /**
     * @brief Constructs a new Player object.
     * @author Samuel Šimún
     * @date 24.4.2023
     */
    explicit Player();

    /**
     * @brief Updates the player's pixmap based on its current direction.
     * @author Samuel Šimún
     * @date 24.4.2023
     */
    void update_player_pixmap();


    /**
     * @brief Controls the movement of the player in mouse mode.
     * @author Samuel Šimún
     * @date 2.5.2023
     */
    void control_player_mouse();


    /**
     * @brief Loads the pixmap for the player based on its direction.
     * @author Samuel Šimún
     * @date 24.4.2023
     */
    void teleport_player(QPoint);


    /**
     * @brief Returns the next position of the player.
     * @return QPoint Representing the next position of the player.
     * @author Samuel Šimún
     * @date 24.4.2023
     */
    [[nodiscard]] QPoint next_player_position() const;

    //! The target position for the player when in mouse mode
    QPoint mouse_target;

    //! The current position of the player
    QPoint current_position;

    //! The current direction of the player
    Sources::Directions direction = Sources::NONE;

    //! The previous direction of the player
    Sources::Directions previous_direction = Sources::NONE;

    //! A flag indicating whether the player is alive or not
    bool alive;

    //! A flag indicating whether the player has taken damage from walls
    bool wall_dmg = false;

    //! A flag indicating whether the player is in mouse mode.
    bool mouse_mode = false;



private:

    /**
     * @brief Loads the pixmap for the player based on its direction.
     * @author Samuel Šimún
     * @date 24.4.2023
     */
    void load_player_pixmap();


    //! The pixmap for the player facing up
    QPixmap pix_map_player_up ;

    //! The pixmap for the player facing down
    QPixmap pix_map_player_down;

    //! The pixmap for the player facing right
    QPixmap pix_map_player_right;

    //! The pixmap for the player facing left
    QPixmap pix_map_player_left;

};

#endif //ICP_PLAYER_H