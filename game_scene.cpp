//
// Created by samuel on 19.4.2023.
//
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "game_scene.h"
#include <QDebug>
#include "matrix.hpp"
#include "ghost.h"
#include "logger.h"
#include <typeinfo>
#include <iostream>


Game_scene::Game_scene(QObject *parent)
: QGraphicsScene{parent}
{
    Logger* logger = new Logger;
    door_open = false;
    cout << typeid(logger).name() << endl;
    load_pixmaps();
    generate_world();
    load_player();
    if (!Sources::play_log_mode) {
        loop();
        connect(&scene_timer, &QTimer::timeout, this, &Game_scene::loop);
        scene_timer.start(Sources::FPS);
        connect(player, &Player::mousePressEvent, player, &Player::mousePressEvent);
    }
    else {
        loop_spectate();
    }
}

void Game_scene::loop() {
    move_player();
    move_ghost();
    check_for_keys();
    check_for_ghosts();
    logger.order_counter++;
}

void Game_scene::loop_spectate() {

}

void Game_scene::load_pixmaps(){
    wall_pixmap = QPixmap(Sources::Wall_file_destination);
    grass_pixmap = QPixmap(Sources::Grass_file_destination);
    door_closed_pixmap = QPixmap(Sources::Door_closed_file_destination);
    door_open_pixmap = QPixmap(Sources::Door_open_file_destination);
    key_pixmap = QPixmap(Sources::Key_file_destination);
}

void Game_scene::generate_world() {
    
    std::vector<std::vector <char>> Map_i =Sources::Matrix;

    for (int i=0; i < Sources::MAP_HEIGHT; i++){
        if (i == 0 || i == Sources::MAP_HEIGHT - 1){
            for (int k=0; k< Sources::MAP_WIDTH;k++){
                map[i][k] = new QGraphicsPixmapItem();
                map[i][k]->setPixmap(wall_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                walls.emplace_back(k*Sources::size,i*Sources::size);
                map[i][k]->setPos(k*Sources::size, i*Sources::size);
                addItem(map[i][k]);
            }
            continue;
        }

        for (int k=0; k < Sources::MAP_WIDTH; k++){
            if (k == 0 || k == Sources::MAP_WIDTH - 1){
                map[i][k] = new QGraphicsPixmapItem();
                map[i][k]->setPixmap(wall_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                walls.emplace_back(k*Sources::size,i*Sources::size);
                map[i][k]->setPos(k*Sources::size, i*Sources::size);
                addItem(map[i][k]);
                continue;
            }

            map[i][k] = new QGraphicsPixmapItem();
            switch (Map_i[i-1][k-1]) {
                case 'X':
                    map[i][k]->setPixmap(wall_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    walls.emplace_back(k*Sources::size,i*Sources::size);
                    break;
                case 'K':
                    map[i][k]->setPixmap(key_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    keys.emplace_back(k,i);
                    break;
                case '.':
                    map[i][k]->setPixmap(grass_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    break;
                case 'S':
                    player_start = QPoint(k*Sources::size,i*Sources::size);
                    map[i][k]->setPixmap(grass_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    break;
                case 'T':
                    target = QPoint(k, i);
                    map[i][k]->setPixmap(door_closed_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    break;
                case 'G':
                    map[i][k]->setPixmap(grass_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    map[i][k]->setPos(k*Sources::size, i*Sources::size);
                    addItem(map[i][k]);
                    Game_scene::load_ghost(QPoint(k*Sources::size,i*Sources::size));
                    continue;
            }
            map[i][k]->setPos(k*Sources::size, i*Sources::size);
            addItem(map[i][k]);
        }
    }
}


void Game_scene::load_player(){
    player = new Player;
    player->setFocus();
    player->teleport_player(player_start);
    addItem(player);
}

bool Game_scene::check_intersection(QPoint first, QPoint second){
    if (first.x() < second.x()){
        if (first.x() + Sources::size > second.x()){
            if (first.y() < second.y()){
                if (first.y() + Sources::size > second.y()){
                    return true;
                }
            }
            else {
                if (first.y() - Sources::size < second.y()){
                    return true;
                }
            }
        }
    }
    else {
        if (first.x() - Sources::size < second.x()){
            if (first.y() < second.y()){
                if (first.y() + Sources::size > second.y()){
                    return true;
                }
            }
            else {
                if (first.y() - Sources::size < second.y()){
                    return true;
                }
            }
        }
    }
    return false;
}

void Game_scene::move_player(){
    QPoint next_position = player->next_player_position();
    qDebug() <<"Curent : " << next_position;
    for (auto & wall : walls){
        if (check_intersection(next_position,wall)){
            player->direction = player->previous_direction;
            logger.add_position_player(next_position, player->direction);
            return;
        }
    }

    if (door_open && check_intersection(next_position, QPoint(target.x()*Sources::size, target.y()*Sources::size))){
        player->direction = Player::NONE;
        scene_timer.stop();
        logger.end_log();
        qDebug() << "WIN";
    }

    player->update_player_pixmap();
    player->setPos(next_position);
    player->current_position = next_position;
    player->previous_direction = player->direction;
    logger.add_position_player(next_position, player->direction);
}

void Game_scene::check_for_keys() {
    for (auto & key : keys){
        if (check_intersection(player->current_position, QPoint(key.x()*Sources::size, key.y()*Sources::size))){
            map[key.y()][key.x()]->setPixmap(grass_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
            keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
            return;
        }
    }

    if (keys.empty()) {
        map[target.y()][target.x()]->setPixmap(
                door_open_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
        door_open = true;
    }


}

void Game_scene::check_for_ghosts() {
    for (auto & ghost : ghosts){
        if (check_intersection(ghost->current_position, player->current_position)){
            player->alive = false;
            scene_timer.stop();
        }
    }

    if (!player->alive){
        for (auto & ghost : ghosts){
            ghost->ghost_timer.stop();
        }
    }

}

void Game_scene::load_ghost(QPoint position) {
    Ghost *new_ghost = new Ghost(player, &logger);
    ghosts.push_back(new_ghost);
    new_ghost->move_ghost(position);
    addItem(new_ghost);
}

///primitive moving through the walls
void Game_scene::move_ghost(){

    QPoint target_position = player->next_player_position();
    for (int i =0; i < ghosts.size();i++){

        if(target_position.y() > ghosts[i]->current_position.y()){


            if (target_position.x() > ghosts[i]->current_position.x()){

            }
            else{

            }

        }
        else {

            if (target_position.x() > ghosts[i]->current_position.x()){

            }
            else{

            }

        }
        //logger.add_position_ghost(i, ghosts[i]->current_position,dir);
    }

}
