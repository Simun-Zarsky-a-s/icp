#include <QApplication>
#include "game_view.h"

int create_window_p(int argc,char  *argv[]){
    QApplication a(argc, argv);

    Game_view view;
    view.show();

    return a.exec();
}