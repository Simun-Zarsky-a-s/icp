/**
    * Project: ICP 2022/23
    *
    * @brief Implementation of user interface before and after game
    * @file welcomeWin.cpp
    * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
    */

#include "welcomeWin.h"
#include <QApplication>
#include "game_view.h"
#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <string>
#include "logger.h"
#include <QString>
#include <QFont>
#include <QComboBox>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QMovie>
#include <QPixmap>
#include <QTextEdit>
#include <QInputDialog>

WelcomeWin::WelcomeWin(QWidget *parent)
        : QMainWindow(parent)
{
    //style of welcome window
    this->setStyleSheet("QWidget {\n"
                        "    background-color: #1E90FF;\n"
                        "}"
                        "QPushButton#log_button:hover {\n"
                        "    background-color: rgb(224, 255, 0);\n"
                        "}"
                        "QPushButton\n"
                        "{\n"
                        "  border: 2px solid gray;\n"
                        "  border-radius: 10px;\n"
                        "  padding: 0 8px;\n"
                        "  background: yellow;\n"
                        "}"
                        "QPushButton:hover:!pressed\n"
                        "{\n"
                        "  background-color: rgb(224, 255, 0);\n"
                        "}"


    );

    //background
    auto *background = new QLabel(this);
    background->setGeometry(QRect(QPoint(0, 0), QSize(1200, 1200)));

    //pacman picture
    auto *pic_label = new QLabel(this);
    QPixmap pic(Sources::Player_file_destination);
    pic_label->setPixmap( pic.scaled(100, 100, Qt::KeepAspectRatio));
    pic_label->show();
    pic_label->setGeometry(QRect(QPoint(75, 0), QSize(200, 200)));

    //title
    auto *main_label = new QLabel(this);
    main_label->setText("PACMAN");
    main_label->setGeometry(QRect(175,50,500,80));
    main_label->setStyleSheet("QLabel { font-weight: bold; }");
    QFont f("Helvetica",50);        //Setting the default font size to 50
    main_label->setFont(f);

    //start game
    start_button = new QPushButton("Start Game", this);
    start_button->setGeometry(QRect(QPoint(200, 140), QSize(225, 50)));
    connect(start_button, &QPushButton::released, this, &WelcomeWin::start_game);

    //choose map
    map_button = new QPushButton("Choose map", this);
    map_button->setGeometry(QRect(QPoint(200, 195), QSize(225, 50)));
    connect(map_button, &QPushButton::released, this, &WelcomeWin::open_map);

    //choose lof file
    file_button = new QPushButton("Choose log file", this);
    file_button->setGeometry(QRect(QPoint(200, 250), QSize(225, 50)));
    connect(file_button, &QPushButton::released, this, &WelcomeWin::open_file);

    //mode game
    game_button = new QPushButton("Game", this);
    game_button->setGeometry(QRect(QPoint(198, 315), QSize(110, 48)));
    game_button->setStyleSheet("background-color: red");
    connect(game_button, &QPushButton::released, this, &WelcomeWin::mode_game);

    //mode log
    log_button = new QPushButton("Log player", this);
    log_button->setGeometry(QRect(QPoint(313, 315), QSize(110, 48)));
    connect(log_button, &QPushButton::released, this, &WelcomeWin::mode_log);

    //set fps
    fps_button = new QPushButton("Set FPS", this);
    fps_button->setGeometry(QRect(QPoint(198, 375), QSize(110, 48)));
    connect(fps_button, &QPushButton::released, this, &WelcomeWin::set_fps);

    //set speed
    speed_button = new QPushButton("Ghost speed", this);
    speed_button->setGeometry(QRect(QPoint(313, 375), QSize(110, 48)));
    connect(speed_button, &QPushButton::released, this, &WelcomeWin::set_speed);

    //set number of lives
    lives_button = new QPushButton("Number of lives", this);
    lives_button->setGeometry(QRect(QPoint(200, 430), QSize(225, 48)));
    connect(lives_button, &QPushButton::released, this, &WelcomeWin::set_lives);

    //default settings info
    auto *label1 = new QLabel(this);
    label1->setText("Default settings: \n Map:  ../examples/map.txt \n Logs:  log.txt \n Mode:  game \n FPS:  100 ");
    label1->setGeometry(QRect(203,490,200,80));
    label1->setStyleSheet("QLabel { font-size: 15px; }");

    //authors
    auto *info = new QLabel(this);
    info->setText("ICP Project 2023. Authors: xsimun04, xzarsk04");
    info->setGeometry(QRect(150,560,400,40));



}

void WelcomeWin::start_game()
{
    Sources::game = true;
    QApplication::quit();


}
void WelcomeWin::open_map()
{
    QString path = QFileDialog::getOpenFileName();
    if(!path.isEmpty()) { //empty path means user canceled the dialog
        qDebug() << path;
        Sources::Map_file_destination = path;
        Resources res(Sources::Map_file_destination);;
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
       if(!Sources::play_log_mode){
           Sources::log_file = path.toStdString();
       }else{
           Sources::log_file = path.toStdString();
           Sources::Map_file_destination = path;
           Resources res(Sources::Map_file_destination);;
           Sources::MAP_WIDTH = res.get_width();
           Sources::MAP_HEIGHT = res.get_height();
           Sources::Matrix = Resources::get_matrix();
       }


    }


}

void WelcomeWin::mode_game()
{
    game_button->setStyleSheet("background-color: red");
    log_button->setStyleSheet("background-color: yellow");
    Sources::play_log_mode = false;

}

void WelcomeWin::mode_log()
{
    log_button->setStyleSheet("background-color: red");
    game_button->setStyleSheet("background-color: yellow");
    Sources::play_log_mode = true;

}

void WelcomeWin::set_speed() {

    auto *pic_label = new QLabel(this);
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                 tr("The bigger the number the slower the ghosts:"), 16, 0, 100, 1, nullptr);

    pic_label->show();
    Sources::GHOST_SWIFT = stoi(tr("%1%").arg(i).toStdString());
    qDebug() << Sources::GHOST_SWIFT;
}

void WelcomeWin::set_fps() {

    auto *pic_label = new QLabel(this);
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                 tr("The bigger the number the slower the ghosts:"), 100, 0, 1000, 1, nullptr);

    pic_label->show();
    Sources::FPS = stoi(tr("%1%").arg(i).toStdString());
    qDebug() << Sources::FPS;
}

void WelcomeWin::set_lives() {
    auto *pic_label = new QLabel(this);
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                 tr("How many times can you touch the ghost:"), 3, 0, 1000, 1, nullptr);
    pic_label->show();
    Sources::number_of_lives = stoi(tr("%1%").arg(i).toStdString());
    qDebug() << "lives" << Sources::number_of_lives;
}

EndWin::EndWin(QWidget *parent)  : QMainWindow(parent)
{
    //end window style
    this->setStyleSheet("QWidget {\n"
                        "    background-color: #1E90FF;\n"
                        "}"
                        "QPushButton\n"
                        "{\n"
                        "  border: 2px solid gray;\n"
                        "  border-radius: 10px;\n"
                        "  padding: 0 8px;\n"
                        "  background: yellow;\n"
                        "}"

    );
    //background
    auto *background = new QLabel(this);
    background->setGeometry(QRect(QPoint(0, 0), QSize(1200, 1200)));

    //pacman
    auto *pic_label = new QLabel(this);
    QPixmap pic(Sources::Player_file_destination);
    pic_label->setPixmap( pic.scaled(100, 100, Qt::KeepAspectRatio));
    pic_label->show();
    pic_label->setGeometry(QRect(QPoint(75, 0), QSize(200, 200)));

    //tittle
    auto *main_label = new QLabel(this);
    main_label->setText("PACMAN");
    main_label->setGeometry(QRect(175,50,500,80));
    main_label->setStyleSheet("QLabel { font-weight: bold; }");
    QFont f("Helvetica",50);        //Setting the default font size to 50
    main_label->setFont(f);

    //game result
    auto *win_label = new QLabel(this);
    if(Sources::win){
        win_label->setText("Congratulations, you won!");
    }else{
        win_label->setText("Maybe next time. Try again!");
    }
    win_label->setGeometry(QRect(125,150,500,40));
    win_label->setStyleSheet("QLabel { font-weight: bold; color = red}");
    QFont ff("Helvetica",20);        //Setting the default font size to 50
    win_label->setFont(ff);

    //new game
    new_button = new QPushButton("New game!", this);
    new_button->setGeometry(QRect(QPoint(200, 200), QSize(200, 50)));
    connect(new_button, &QPushButton::released, this, &EndWin::new_game);

    //end game
    end_button = new QPushButton("Quit Pacman", this);
    end_button->setGeometry(QRect(QPoint(200, 300), QSize(200, 50)));
    connect(end_button, &QPushButton::released, this, &EndWin::end_game);


}

void EndWin::end_game() {
    EndWin::result = 0;
    Sources::game = false;
    QApplication::quit();
}

void EndWin::new_game() {
    EndWin::result = 1;
    Sources::game = true;
    QApplication::quit();
}
