

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
    void open_file();
private:
    QPushButton *start_button;
    QPushButton *file_button;
};
#endif //ICP_WELCOMEWIN_H
