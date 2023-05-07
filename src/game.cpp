/**
    * Project: ICP 2022/23
    *
    * @brief Implementation of game windows
    * @file game.cpp
    *  @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
    */


#include <QApplication>
#include "welcomeWin.h"
#include "game_view.h"


int create_window_p(int argc,char  *argv[]){ ///welcome window
    QApplication a(argc, argv);

    WelcomeWin welcome_win;
    welcome_win .setFixedHeight(600);
    welcome_win .setFixedWidth(600);
    welcome_win .showNormal();
    return QApplication::exec();
}

int create_window_g(int argc,char  *argv[]){ ///game_window
    QApplication a(argc, argv);

    Game_view view;
    view.show();

    return QApplication::exec();
}

int create_window_end(int argc,char  *argv[]){ ///welcome window
    QApplication a(argc, argv);

    EndWin welcome_win;
    welcome_win .setFixedHeight(600);
    welcome_win .setFixedWidth(600);
    welcome_win .showNormal();
    QApplication::exec();

    return welcome_win.result;
}