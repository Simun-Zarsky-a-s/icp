/**
    * Project: ICP 2022/23
    *
    * @brief Implementation of logging
    * @file logger.cpp
    *  @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    *
    */


#include "logger.h"
#include <sstream>
#include <string>
#include <iostream>
#include <QDebug>

Logger::Logger() = default;


void Logger::open_file_output() {
    file_output.open(Sources::log_file);

    if (file_output.fail())
        exit (1);

    add_map_to_file();
}

void Logger::open_file_input() {
    file_input.open(Sources::log_file, std::ios::in);

    if (!file_input.is_open())
        exit (1);

    read_input();
}


void Logger::add_map_to_file() {
    file_output << Sources::MAP_HEIGHT - 2 << " " << Sources::MAP_WIDTH - 2 << std::endl;
    std::vector<std::vector <char>> Map_i = Sources::Matrix;

    for (int i=0; i < (int)Map_i.size() - 2; i++) {
        for (int j=0; j < (int)Map_i[i].size() - 2;j++) {
            file_output << Map_i[i][j];
        }
        file_output << std::endl;
    }

    file_output << std::endl << std::endl <<"START" << std::endl;
    order_counter = 1;
}

void Logger::add_position_ghost(int number, QPoint position, Sources::Directions direction) {
    file_output << order_counter << " "<<  "G " << number << " " << direction << " " << position.x() << " " << position.y() << std::endl;
}

void Logger::add_position_player(QPoint position, Sources::Directions direction) {
    file_output << order_counter << " "<< "P " << direction << " " << position.x()<< " " << position.y() << std::endl;
}

void Logger::remove_key(QPoint position) {
    file_output << order_counter << " "<< "K " << position.x()<< " " << position.y() << std::endl;
}

void Logger::end_log() {
    file_output << order_counter << " "<< "E" << std::endl;
    file_output.close();
}

Sources::Directions Logger::extract_direction(int dir){
    switch (dir){
        case 0:
            return Sources::UP;
        case 1:
            return Sources::DOWN;
        case 2:
            return Sources::LEFT;
        case 3:
            return Sources::RIGHT;
        case 4:
            return Sources::NONE;
        default:
            exit(1);
    }
}

void Logger::read_input(){
    std::string line;
    bool skipped_map = false;
    int current = -1;
    string word;
    std::vector<Log> tik_log;

    while (getline(file_input, line)) {
        if (!skipped_map){
            if (line == "START")
                skipped_map = true;
            continue;
        }

        Log current_log;
        std::stringstream ss(line);
        ss >> word;
        if (std::stoi(word) != current){
            current++;
            log_vector.emplace_back(tik_log);
            tik_log.clear();
        }

        ss >> word;

        if (word == "P"){
            current_log.entity = 'P';
            ss >> word;
            current_log.direction = extract_direction(std::stoi(word));

            ss >> word;
            int x = std::stoi(word);

            ss >> word;
            int y = std::stoi(word);
            current_log.position = QPoint(x,y);
        }
        else if (word == "G"){
            current_log.entity = 'G';

            ss >> word;
            current_log.order = std::stoi(word);

            ss >> word;
            current_log.direction = extract_direction(std::stoi(word));

            ss >> word;
            int x = std::stoi(word);

            ss >> word;
            int y = std::stoi(word);
            current_log.position = QPoint(x,y);
        }
        else if (word == "K") {
            current_log.entity = 'K';

            ss >> word;
            int x = std::stoi(word);

            ss >> word;
            int y = std::stoi(word);
            current_log.position = QPoint(x,y);
        }
        else if (word == "E"){
            current_log.entity = 'E';
        }
        tik_log.emplace_back(current_log);
    }
    log_vector.emplace_back(tik_log);
}

std::vector<Logger::Log> Logger::get_instruction_by_index(int index) {
    return log_vector.at(index);
}