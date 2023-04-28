//
// Created by samuel on 26.4.2023.
//

#include "logger.h"
#include <sstream>
#include <string>
#include <iostream>


Logger::Logger() {

    open_file_output();
}


void Logger::open_file_output() {
    file_output.open(Sources::log_file);

    if (file_output.fail())
        exit (1);
}

void Logger::open_file_input() {
    file_input.open(Sources::log_file, std::ios::in);

    if (!file_input.is_open())
        exit (1);
}


void Logger::add_map_to_file() {
    file_output << Sources::MAP_HEIGHT << " " << Sources::MAP_WIDTH << std::endl;
    std::vector<std::vector <char>> Map_i = Resources::get_matrix();

    for (const auto & i : Map_i) {
        for (char j : i) {
            file_output << j << " ";
        }
        file_output << std::endl;
    }

    file_output << std::endl << std::endl <<"START" << std::endl;
    order_counter = 1;
}

void Logger::add_position_ghost(int number, QPoint position, Player::Directions direction) {
    file_output << order_counter << " "<<  "G " << number << " " << direction << " " << position.x() << " " << position.y() << std::endl;
}

void Logger::add_position_player(QPoint position, Player::Directions direction) {
    file_output << order_counter << " "<< "P " << direction << " " << position.x()<< " " << position.y() << std::endl;
}

void Logger::end_log() {
    file_output.close();
}

void Logger::read_input(){
    std::string line;
    bool skiped_map = false;

    while (getline(file_input, line)) {
        if (!skiped_map){
            if (line != "START")
                skiped_map = true;
            continue;
        }

        std::stringstream ss(line);
        //std::vector<Log> new_vector;


    }

}

void Logger::remove_key(QPoint position) {
    file_output << order_counter << " "<< "K " << position.x()<< " " << position.y() << std::endl;
}


