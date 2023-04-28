//
// Created by samuel on 26.4.2023.
//

#ifndef PACMAN_LOGGER_H
#define PACMAN_LOGGER_H

#include <fstream>
#include <QPoint>
#include <vector>
#include "matrix.hpp"
#include "Sources.h"
#include "player.h"


class Logger {
public:
    explicit Logger();

    int order_counter{};
    struct Log {
        int order{};
        char entity{};
        int number{};
        QPoint position;
        Player::Directions direction;
    };

    std::vector<std::vector<Log>> log_vector;

    void open_file_output();
    void open_file_input();
    void add_map_to_file();
    void add_position_ghost(int, QPoint, Player::Directions);
    void add_position_player(QPoint, Player::Directions);
    void remove_key(QPoint);
    void end_log();

private:
    void read_input();
    std::ifstream file_input;
    std::ofstream file_output;
};

#endif //PACMAN_LOGGER_H
