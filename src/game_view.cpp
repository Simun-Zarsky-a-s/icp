/**
    * Project: ICP 2022/23
    *
    * @brief Implementation of game view
    * @file game_view.cpp
    *  @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    *
    */

#include "game_view.h"
#include <QApplication>
#include <QKeyEvent>
#include <cmath>

Game_view::Game_view() : QGraphicsView(), game_scene(new Game_scene(this))
{
    setScene(game_scene);
    resize(ceil(game_scene->width() + 10) ,ceil(game_scene->height() + 10));
}
