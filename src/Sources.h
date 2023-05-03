/**
 * @file Sources.h
 * @brief Library that represent constant for handling program
 * @section Sources
 * @name Sources
 * @date 19.4.2023
 */

#ifndef PACMAN_SOURCES_H
#define PACMAN_SOURCES_H

#include <QPoint>
#include <vector>
#include <QObject>
#include <QPixmap>
#include <QString>

/**
 * @brief The Sources class contains static members used throughout the game
 * @brief These members include constants, file destinations, and game state variables
 * @author Samuel Šimún
 * @author Daniel Žársky
 * @date 24.4.2023
*/
class Sources {
public:
    //! The size of each square in the game grid
    const static int size = 60;

    //! The frames per second used for the game animation
    static int FPS;

    //! The width of the game map
    static int MAP_WIDTH;

    //! The height of the game map
    static int MAP_HEIGHT;

    //! The speed of the player
    static int SWIFT;

    //! The speed of the ghosts
    static int GHOST_SWIFT;

    //! A flag indicating whether the game is in play log mode
    static bool play_log_mode;

    //! The time for which ghosts are frozen
    const static int time_between_dead = 1000;

    /**
     * @brief The Directions enum represents the possible directions the player can move.
     */
    enum Directions{UP,DOWN,LEFT,RIGHT, NONE};

    //! The file destination for the wall pixmap
    static QString Wall_file_destination;

    //! The file destination for the grass pixmap
    static QString Grass_file_destination;

    //! The file destination for the player pixmap
    static QString Player_file_destination;

    //! The file destination for the closed door pixmap
    static QString Door_closed_file_destination;

    //! The file destination for the open door pixmap
    static QString Door_open_file_destination;

    //! The file destination for the key pixmap
    static QString Key_file_destination;

    //! The file destination for the ghost pixmap
    static QString Ghost_file_destination;

    //! The file destination for the game map
    static QString Map_file_destination;

    //QObject target; TODO : NACO ?

    //! A vector of wall objects in the game
    std::vector<QObject> Walls;

    //! A vector of grass objects in the game
    std::vector<QObject> Grass;

    //! A vector of key objects in the game
    std::vector<QObject> Keys;

    //! The file name for the play log
    static std::string log_file;

    //! A flag indicating whether the player has won the game
    static bool win;

    //! A flag indicating whether the game is currently running
    static bool game;

    //! The number of keys the player has collected
    static int number_of_keys;

    //! The number of lives the player has remaining
    static int number_of_lives;


    //!  The game map as a 2D vector of characters
    static std::vector<std::vector <char>> Matrix;
};

#endif //PACMAN_SOURCES_H
