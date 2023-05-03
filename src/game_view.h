/**
 * @file game_view.h
 * @section Game_view
 * @name Game_scene
 * @date 20.4.2023
 */

#ifndef ICP_GAME_VIEW_H
#define ICP_GAME_VIEW_H

#include <QGraphicsView>
#include "game_scene.h"


/**
 * @brief The Game_view class represents a customized QGraphicsView used for displaying the game scene.
 * @author Samuel Šimún
 * @date 20.4.2023
 */
class Game_view : public QGraphicsView
{
    Q_OBJECT
public:

    /**
     * @brief Constructs a new Game_view object.
     * @author Samuel Šimún
     * @date 20.4.2023
     */
    explicit Game_view();

private:
    //! Pointer to Game_scene
    Game_scene *game_scene;

};

#endif //ICP_GAME_VIEW_H