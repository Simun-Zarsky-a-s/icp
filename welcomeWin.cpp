
#include "welcomeWin.h"
#include <QApplication>
#include <QKeyEvent>
#include "game_view.h"
#include <QDebug>
#include <QLabel>

WelcomeWin::WelcomeWin(QWidget *parent)
        : QMainWindow(parent)
{
    start_button = new QPushButton("Start Game", this);

    start_button->setGeometry(QRect(QPoint(200, 200), QSize(200, 50)));

    connect(start_button, &QPushButton::released, this, &WelcomeWin::start_game);
}

void WelcomeWin::start_game()
{
    QApplication::quit();

}


