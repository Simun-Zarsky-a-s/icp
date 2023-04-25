//
// Created by samuel on 19.4.2023.
//
#include "game_view.h"
#include <QApplication>
#include <QKeyEvent>

Game_view::Game_view() : QGraphicsView(), game_scene(new Game_scene(this))
{
    setScene(game_scene);
    resize(800,800);
}
