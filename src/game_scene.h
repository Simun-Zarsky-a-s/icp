/**
 * @file game_scene.h
 * @section Game_scene
 * @name Game_scene
 * @date 19.4.2023
 */

#ifndef ICP_GAME_SCENE_H
#define ICP_GAME_SCENE_H

#include <QGraphicsScene>
#include "player.h"
#include "gamemap.h"
#include "Sources.h"
#include "ghost.h"
#include "logger.h"
#include "matrix.hpp"
#include "ghost.h"
#include <QLabel>

/**
 * @name Game_scene
 * @brief Graphical representation of game and its main logic
 * @author Samuel Šimún
 */
class Game_scene : public QGraphicsScene {
    Q_OBJECT
public:
    //! Constructor of Game_scene
    explicit Game_scene(QObject *parent);

    /**
     * @brief Method which check if there is intersection between two points
     * @param QPoint First point
     * @param QPoint Second point
     * @author Samuel Šimún
     * @return bool Returns true if there is intersection, otherwise false
     */
    static bool check_intersection(QPoint first, QPoint second);


private:
    //! Logger for handling logging and reading from logger
    Logger logger;

    /**
     * @brief Method which will load pixmaps from files
     * @author Samuel Šimún
     * @date 26.4.2023
     */
    void load_pixmaps();


    /**
     * @brief Main loop for game mode
     * @author Samuel Šimún
     * @date 20.4.2023
     */
    void loop();


    /**
     * @brief Method for generating map for game
     * @author Samuel Šimún
     * @date 20.4.2023
     */
    void generate_world();


    /**
     * @brief Method which create player and set it to correct position
     * @author Samuel Šimún
     * @date 24.4.2023
     */
    void load_player();


    /**
     * @brief Moves player to position which is defined in players object
     * @author Samuel Šimún
     * @date 25.4.2023
     */
    void move_player();


    /**
     * @brief Load all ghost which were detected in map generation and sets its positions
     * @author Samuel Šimún
     * @date 1.5.2023
     */
    void load_ghosts();


    /**
     * @brief Check if there is any intersection with keys, if all keys were collected, doors will be opened
     * @author Samuel Šimún
     * @date 26.4.2023
     */
    void check_for_keys();


    /**
     * @brief Check if there is any intersection with ghost
     * @brief If intersection is detected game will be ended
     * @author Samuel Šimún
     * @date 26.4.2023
     */
    void check_for_ghosts();


    /**
     * @brief Main loop for Player mode
     * @author Samuel Šimún
     * @date 2.5.2023
     */
    void loop_spectate();


    /**
     * @brief Method which set position on scene from ghost object
     * @author Samuel Šimún
     * @date 1.5.2023
     */
    void update_ghost();

    /**
   * @brief Method which show number of keys left
   * @author Samuel Šimún
   * @date 1.5.2023
   */
    void update_stats();


    /**
     * @brief Method which will pause all ghosts
     * @author Samuel Šimún
     * @date 3.5.2023
     */
    void pause_ghosts();


    /**
     * @brief Method which handle Mouse Click
     * @author Samuel Šimún
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;


    /**
     * @brief Method which handle Key Press
     * @author Samuel Šimún
     * @param event
     */
    void keyPressEvent(QKeyEvent *event) override;


    //! Pointer to player
    Player* player{};

    //! Timer which call main loops
    QTimer scene_timer;

    //! Timer for pause when there is intersection between ghost and player
    QTimer p_timer;
    bool paused = false;

    //! Command for log mode
    Sources::Directions command = Sources::NONE;
    Sources::Directions previous_command = Sources::NONE;

    //! Pixmaps of items on map
    QPixmap wall_pixmap;
    QPixmap grass_pixmap;
    QPixmap door_closed_pixmap;
    QPixmap door_open_pixmap;
    QPixmap key_pixmap;

    QLabel stats;

    //! Graphical representation of map
    QGraphicsPixmapItem* map[100][100]{};
    std::vector<QPoint> walls;
    std::vector<QPoint> keys;
    std::vector<Ghost*> ghosts;


    //! Important points for handling events
    QPoint player_start;
    QPoint target;
    std::vector<QPoint> ghost_to_be_loaded;

    bool door_open = false;
    bool fast_forward = false;
    int current_index = 0;
};


#endif //ICP_GAME_SCENE_H