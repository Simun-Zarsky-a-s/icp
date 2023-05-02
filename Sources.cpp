//
// Created by samuel on 20.4.2023.
//
#include <iostream>
#include "Sources.h"
#include <QString>
#include "matrix.hpp"

QString Sources::Wall_file_destination = ":/content/wall.jpg";
QString Sources::Grass_file_destination = ":/content/grass.png";
QString Sources::Door_closed_file_destination = ":/content/dvierka_closed.jpg";
QString Sources::Door_open_file_destination = ":/content/dvierka_open.jpg";
QString Sources::Key_file_destination = ":/content/key.webp";
QString Sources::Ghost_file_destination = ":/content/ghost.png";

QString Sources::Map_file_destination = "../examples/map.txt";//default value

Resources res(Sources::Map_file_destination.toStdString());;
int Sources::MAP_WIDTH = res.get_width();
int Sources::MAP_HEIGHT = res.get_height();
vector<vector<char>> Sources::Matrix = Resources::get_matrix();

std::string Sources::log_file = "log.txt";//default value

bool Sources::play_log_mode = false; //default mode game



