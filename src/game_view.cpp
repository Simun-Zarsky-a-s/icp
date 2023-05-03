//
// Created by samuel on 19.4.2023.
//


#include "game_view.h"
#include <QApplication>
#include <QKeyEvent>
#include <cmath>

Game_view::Game_view() : QGraphicsView(), game_scene(new Game_scene(this))
{
    setScene(game_scene);
    resize(ceil(game_scene->width() + 10) ,ceil(game_scene->height() + 10));
}
