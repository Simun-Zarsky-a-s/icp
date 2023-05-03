/**
    * Project: ICP 2022/23
    *
    * @brief Implementation of game scene
    * @file game_scene.cpp
    *  @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
    */

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "game_scene.h"
#include <QDebug>
#include <iostream>
#include <QApplication>
#include <unistd.h>


Game_scene::Game_scene(QObject *parent)
: QGraphicsScene{parent}
{
    load_pixmaps();
    generate_world();
    load_player();
    load_ghosts();

    if (!Sources::play_log_mode) {
        logger.open_file_output();
        loop();
        connect(&scene_timer, &QTimer::timeout, this, &Game_scene::loop);
        scene_timer.start(Sources::FPS);
    }
    else {
        logger.open_file_input();
        loop_spectate();
        connect(&scene_timer, &QTimer::timeout, this, &Game_scene::loop_spectate);
        scene_timer.start(Sources::FPS);

    }
}

void Game_scene::loop() {

    move_player();
    update_ghost();
    check_for_keys();
    check_for_ghosts();
    update_stats();
    logger.order_counter++;
}

void Game_scene::loop_spectate() {
    bool forward = false;
    update_stats();

    if (command == Sources::NONE)
        return;

    if (command == Sources::RIGHT){
        forward = true;
        current_index++;
    }
    else if (command == Sources::LEFT && current_index > 1){
        current_index--;
    }
    else {
        return;
    }

    std::vector<Logger::Log> tik_log = logger.get_instruction_by_index(current_index);
    for (auto log : tik_log){
        if (log.entity == 'P'){
            player->teleport_player(log.position);
            player->direction = log.direction;
            player->update_player_pixmap();
        }
        else if (log.entity == 'G'){
            ghosts[log.order]->teleport(log.position);
            ghosts[log.order]->direction = log.direction;
            ghosts[log.order]->change_pixmap();
        }
        else if (log.entity == 'K'){
            if (forward) {
                map[log.position.x()][log.position.y()]->setPixmap(
                        grass_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                keys.erase(std::remove(keys.begin(), keys.end(), QPoint(log.position.y(), log.position.x())), keys.end());

                if (keys.empty()){
                    map[target.y()][target.x()]->setPixmap(
                            door_open_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    door_open = true;
                }
            }
            else{
                map[log.position.x()][log.position.y()]->setPixmap(key_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                keys.emplace_back(log.position.y(),log.position.x());
                if (door_open){
                    map[target.y()][target.x()]->setPixmap(
                            door_closed_pixmap.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    door_open = false;
                }
            }
        }
        else if (log.entity == 'E'){
            current_index--;
        }
    }

    if (!fast_forward)
        command = Sources::NONE;

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
                    Sources::number_of_keys += 1;
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
                    ghost_to_be_loaded.emplace_back(k*Sources::size,i*Sources::size);
                    break;
            }
            map[i][k]->setPos(k*Sources::size, i*Sources::size);
            addItem(map[i][k]);
        }
    }
}


void Game_scene::load_player(){
    player = new Player;
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

    if (player->mouse_mode)
        player->control_player_mouse();

    QPoint next_position = player->next_player_position();
    for (auto & wall : walls){
        if (check_intersection(next_position,wall)){
            player->direction = player->previous_direction;
            player->wall_dmg = true;
            logger.add_position_player(next_position, player->direction);
            return;
        }
    }

    player->wall_dmg = false;

    if (door_open && check_intersection(next_position, QPoint(target.x()*Sources::size, target.y()*Sources::size))){
        player->direction = Sources::NONE;
        scene_timer.stop();
        logger.end_log();
        Sources::win = true;
        Sources::game = true;
        QApplication::quit();

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
            logger.remove_key(QPoint(key.y(), key.x()));
            Sources::number_of_keys -=1;
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
    if (paused)
        return;

    for (auto & ghost : ghosts){
        if (check_intersection(ghost->current_position, player->current_position)){

            if(Sources::number_of_lives < 2){
                player->alive = false;
                scene_timer.stop();
            }

            Sources::number_of_lives -=1;

            pause_ghosts();
        }
    }

    if (!player->alive){
        for (auto & ghost : ghosts){
            ghost->ghost_timer.stop();
        }
        Sources::win = false;
        Sources::game = true;

        Sources::number_of_lives -=1;
        const int delay = 1000000;
        usleep(delay);

        logger.end_log();
        QApplication::quit();
    }

}

void Game_scene::load_ghosts() {
    int order = 0;
    for (auto position : ghost_to_be_loaded) {
        auto *new_ghost = new Ghost(player);
        ghosts.push_back(new_ghost);
        new_ghost->move_ghost(position);
        new_ghost->ghost_order = order;
        order++;
        addItem(new_ghost);
    }
}

void Game_scene::update_ghost(){
    if (paused)
        return;

    bool valid =true;
    for(auto & ghost : ghosts){

        ghost->get_next_direction(player->current_position, ghost->change);//change strategy
        QPoint next_point = ghost->get_next_position(); //get next position

        for (auto & wall : walls){ //check intersections
            if (check_intersection(next_point,wall)){
                logger.add_position_ghost(ghost->ghost_order, next_point, ghost->direction);
                ghost->change = !ghost->change;
                valid = false;
                break;
            }
            valid = true;
            //next_point = ghosts[i]->get_next_position();

        }
        if (valid){
            ghost->move_ghost(next_point);
            ghost->change_pixmap();
        }

        logger.add_position_ghost(ghost->ghost_order, next_point, ghost->direction);//log the position

    }

}

void Game_scene::pause_ghosts(){
    paused = true;
    p_timer.setSingleShot(true);
    p_timer.start(Sources::time_between_dead);
    connect(&p_timer, &QTimer::timeout, [=](){
        paused = false;
    });
}

void Game_scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    player->mouse_mode = true;
    player->mouse_target = event->scenePos().toPoint();
    QGraphicsScene::mousePressEvent(event);
}

void Game_scene::keyPressEvent(QKeyEvent *event) {
    player->mouse_mode = false;

    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            player->direction = Sources::UP;
            command = Sources::RIGHT;
            fast_forward = true;
            break;

        case Qt::Key_S:
        case Qt::Key_Down:
            player->direction = Sources::DOWN;
            command = Sources::LEFT;
            fast_forward = true;
            break;

        case Qt::Key_D:
        case Qt::Key_Right:
            player->direction = Sources::RIGHT;
            command = Sources::RIGHT;
            fast_forward = false;
            break;

        case Qt::Key_A:
        case Qt::Key_Left:
            player->direction = Sources::LEFT;
            command = Sources::LEFT;
            fast_forward = false;
            break;

        case Qt::Key_Space:
            fast_forward = false;
            if (scene_timer.isActive())
                scene_timer.stop();
            else
                scene_timer.start();

        default:
            break;
    }

    QGraphicsScene::keyPressEvent(event);
}

void Game_scene::update_stats() { //print info about lives and keys
    QString number_of_keys = QString::fromStdString(to_string(Sources::number_of_keys));
    QGraphicsTextItem *text = this->addText(number_of_keys);
    text->setPos(0, 0);

    text->setHtml(QString("<div style='background:rgba(255, 255, 255, 100%);'>") +QString("NUMBER OF KEYS:   ") + number_of_keys +QString("   </div>") );
    QString lives;
    lives = QString::fromStdString(to_string((Sources::number_of_lives)));

    QGraphicsTextItem *lives_text = this->addText(lives);
    text->setPos(0, 20);

    lives_text->setHtml(QString("<div style='background:rgba(255, 255, 255, 100%);'>") +QString("NUMBER OF LIVES: ")+ lives + QString("  </div>") );
}
