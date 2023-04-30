
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
#include <qfontmetrics.h>
#include <QFont>
#include <QComboBox>
#include <QVBoxLayout>

WelcomeWin::WelcomeWin(QWidget *parent)
        : QMainWindow(parent)
{

    QLabel *main_label = new QLabel(this);
    main_label->setText("PACMAN");
    main_label->setGeometry(QRect(150,50,500,80));
    main_label->setStyleSheet("QLabel { font-weight: bold; }");
    QFont f("Helvetica",50);        //Setting the default font size to 50
    QFontMetrics fm(f);
    main_label->setFont(f);



    start_button = new QPushButton("Start Game", this);

    start_button->setGeometry(QRect(QPoint(200, 150), QSize(200, 50)));

    connect(start_button, &QPushButton::released, this, &WelcomeWin::start_game);

    map_button = new QPushButton("Choose map", this);

    map_button->setGeometry(QRect(QPoint(200, 200), QSize(200, 50)));

    connect(map_button, &QPushButton::released, this, &WelcomeWin::open_map);

    file_button = new QPushButton("Choose log file", this);

    file_button->setGeometry(QRect(QPoint(200, 250), QSize(200, 50)));

    connect(file_button, &QPushButton::released, this, &WelcomeWin::open_file);

    game_button = new QPushButton("Mode game", this);

    game_button->setGeometry(QRect(QPoint(200, 300), QSize(100, 50)));

    connect(game_button, &QPushButton::released, this, &WelcomeWin::mode_game);

    log_button = new QPushButton("Mode log", this);

    log_button->setGeometry(QRect(QPoint(300, 300), QSize(100, 50)));

    connect(log_button, &QPushButton::released, this, &WelcomeWin::mode_log);

    QLabel *label1 = new QLabel(this);
    label1->setText("Default settings: \n Map:  ../examples/map.txt \n Logs:  log.txt");
    label1->setGeometry(QRect(200,450,200,80));

    QLabel *info = new QLabel(this);
    info->setText("ICP Project 2023. Authors: xsimun04, xzarsk04");
    info->setGeometry(QRect(150,560,400,40));

}

void WelcomeWin::start_game()
{
    QApplication::quit();

}
void WelcomeWin::open_map()
{

    QString path = QFileDialog::getOpenFileName();
    if(!path.isEmpty()) { //empty path means user canceled the dialog
        qDebug() << path;
        Sources::Map_file_destination = path;
        Resources res(Sources::Map_file_destination.toStdString());;
         Sources::MAP_WIDTH = res.get_width();
         Sources::MAP_HEIGHT = res.get_height();
         Sources::Matrix = Resources::get_matrix();
    }

}
void WelcomeWin::open_file()
{

    QString path = QFileDialog::getOpenFileName();
    if(!path.isEmpty()) { //empty path means user canceled the dialog
       qDebug() << path;
       Sources::log_file = path.toStdString();
    }


}

void WelcomeWin::mode_game()
{
    game_button->setStyleSheet("background-color: red");
    log_button->setStyleSheet("background-color: white");
    Sources::mode = 0;

}

void WelcomeWin::mode_log()
{
    log_button->setStyleSheet("background-color: red");
    game_button->setStyleSheet("background-color: white");
    Sources::mode = 1;

}

