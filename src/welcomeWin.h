

#ifndef ICP_WELCOMEWIN_H
#define ICP_WELCOMEWIN_H

#include <QMainWindow>
#include <QPushButton>
#include "Sources.h"


class WelcomeWin : public QMainWindow
{
Q_OBJECT
public:
    explicit WelcomeWin(QWidget *parent = nullptr);

private slots:
    static void start_game();
    static void open_map();
    static void open_file();
    void mode_game();
    void mode_log();

private:
    QPushButton *start_button;
    QPushButton *map_button;
    QPushButton *file_button;
    QPushButton *game_button;
    QPushButton *log_button;
};

class EndWin : public QMainWindow
{
Q_OBJECT
public:
    explicit EndWin(QWidget *parent = nullptr);
    int result =0;
private slots:
    void end_game();
    void new_game();

private:
    QPushButton *end_button;
    QPushButton *new_button;

};
#endif //ICP_WELCOMEWIN_H
