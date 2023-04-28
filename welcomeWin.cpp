
#include "welcomeWin.h"
#include <QApplication>
#include <QKeyEvent>
#include "game_view.h"
#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <string>
#include "logger.h"
#include <QString>

WelcomeWin::WelcomeWin(QWidget *parent)
        : QMainWindow(parent)
{

    start_button = new QPushButton("Start Game", this);

    start_button->setGeometry(QRect(QPoint(200, 200), QSize(200, 50)));

    connect(start_button, &QPushButton::released, this, &WelcomeWin::start_game);

    file_button = new QPushButton("Choose log file", this);

    file_button->setGeometry(QRect(QPoint(200, 300), QSize(200, 50)));

    connect(file_button, &QPushButton::released, this, &WelcomeWin::open_file);

}

void WelcomeWin::start_game()
{
    QApplication::quit();

}

void WelcomeWin::open_file()
{

    QString path = QFileDialog::getOpenFileName();
    if(!path.isEmpty()) { //empty path means user canceled the dialog
       qDebug() << path;
       Sources::log_file = path.toStdString();
    }


}

