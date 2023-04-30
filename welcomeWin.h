

#ifndef ICP_WELCOMEWIN_H
#define ICP_WELCOMEWIN_H

#include <QMainWindow>
#include <QPushButton>


class WelcomeWin : public QMainWindow
{
Q_OBJECT
public:
    explicit WelcomeWin(QWidget *parent = nullptr);

private slots:
    void start_game();
    void open_map();
    void open_file();
    void mode_game();
    void mode_log();
private:
    QPushButton *start_button;
    QPushButton *map_button;
    QPushButton *file_button;
    QPushButton *game_button;
    QPushButton *log_button;
};
#endif //ICP_WELCOMEWIN_H
