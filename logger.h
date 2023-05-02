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
        Sources::Directions direction;
    };

    void open_file_output();
    void open_file_input();
    void add_map_to_file();
    void add_position_ghost(int, QPoint, Sources::Directions);
    void add_position_player(QPoint, Sources::Directions);
    void remove_key(QPoint);
    void end_log();
    static Sources::Directions extract_direction(int);
    std::vector<Logger::Log> get_instruction_by_index(int);



private:
    void read_input();
    std::vector<std::vector<Log>> log_vector;
    std::ifstream file_input;
    std::ofstream file_output;
};

#endif //PACMAN_LOGGER_H
