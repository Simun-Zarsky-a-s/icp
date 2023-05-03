/**
    * Project: ICP 2022/23
    *
    * @brief Library for user interfaces before and after game
    * @file welcomeWin.h
    * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
    *
    */

#ifndef ICP_WELCOMEWIN_H
#define ICP_WELCOMEWIN_H

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include "Sources.h"
#include <QLineEdit>

/**
 *  Class representing user interfaces at the beginning of a game
 */
class WelcomeWin : public QMainWindow
{
Q_OBJECT
public:
    /**
     * Constructor of the welcome window at the beginning
     * @param parent Parent QWidget
     */
    explicit WelcomeWin(QWidget *parent = nullptr);

private slots:
    /**
     * Ends welcome window and starts game
     */
    static void start_game();
    /**
     * Opens file manager and assigns selected file to sources src_file
     */
    static void open_map();
    /**
     * Opens file manager and assigns selected file to sources Map_file_destination
     */
    static void open_file();
    /**
     * Selects mode game
     */
    void mode_game();
    /**
     * Selects mode log
     */
    void mode_log();
    /**
     * Set speed of the ghost, the bigger the value  the slower the ghost
     */
    void set_speed();
    /**
     * Set frames per second in the game
     */
    void set_fps();
    /**
     * Set number of lives (how many times can player touch the ghost)
     */
    void set_lives();

private:
    QPushButton *start_button; //! start game
    QPushButton *map_button; //! select map
    QPushButton *file_button; //! choose file for logging
    QPushButton *game_button; //!mode game
    QPushButton *log_button; //!mode log
    QPushButton *fps_button; //! set fps
    QPushButton *speed_button; //!set speed of ghosts
    QPushButton *lives_button; //! set number of lives

};

/**
 *  Class representing user interfaces at the end of a game
 */
class EndWin : public QMainWindow
{
Q_OBJECT
public:
    explicit EndWin(QWidget *parent = nullptr);
    int result =0;
private slots:
    /**
     * Ends application
     */
    void end_game();
    /**
     * Returns back to the welcome window
     */
    void new_game();

private:
    QPushButton *end_button; //!end app
    QPushButton *new_button; //!continue playing

};
#endif //ICP_WELCOMEWIN_H
