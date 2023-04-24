//
// Created by samuel on 19.4.2023.
//
#include "game_view.h"
#include <QApplication>
#include <QKeyEvent>

Game_view::Game_view() : QGraphicsView(), game_scene(new Game_scene(this))
{
    setScene(game_scene);
}
/// Pokial stlaci uzivatel escape, hra sa konci
void Game_view::KeyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape)
        QApplication::instance()->quit();
}
