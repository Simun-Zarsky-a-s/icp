//
// Created by samuel on 19.4.2023.
//
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QPixmap>
#include "game_scene.h"
#include <QDebug>


Game_scene::Game_scene(QObject *parent)
: QGraphicsScene{parent}
{
    //setSceneRect(0,0, Gamemap::MAP_WIDTH, Gamemap::MAP_HEIGHT);
    generate_world();
    load_player();
    loop();
    connect(&scene_timer, &QTimer::timeout, this, &Game_scene::loop);
    scene_timer.start(Sources::FPS);
}

void Game_scene::loop() {
    move_player();
}

void Game_scene::generate_world() {
    std::vector<std::vector <char>> Map_i = {
            {'.', '.', 'X','X'},
            {'.', '.', 'X', 'X'},
            {'X', '.', 'X', 'X'},
            {'.', '.', 'S','.'}
    };

    QPixmap wall("/home/samuel/Desktop/BIT/ICP/Projekt/icp/content/wall.jpg");
    QPixmap grass("/home/samuel/Desktop/BIT/ICP/Projekt/icp/content/grass.png");

    for (int i=0; i < Sources::MAP_HEIGHT; i++){
        if (i == 0 || i == Sources::MAP_HEIGHT - 1){
            for (int k=0; k< Sources::MAP_WIDTH;k++){
                map[i][k] = new QGraphicsPixmapItem();
                map[i][k]->setPixmap(wall.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                walls.emplace_back(k*Sources::size,i*Sources::size);
                map[i][k]->setPos(k*Sources::size, i*Sources::size);
                addItem(map[i][k]);
            }
            continue;
        }

        for (int k=0; k < Sources::MAP_WIDTH; k++){
            if (k == 0 || k == Sources::MAP_WIDTH - 1){
                map[i][k] = new QGraphicsPixmapItem();
                map[i][k]->setPixmap(wall.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                walls.emplace_back(k*Sources::size,i*Sources::size);
                map[i][k]->setPos(k*Sources::size, i*Sources::size);
                addItem(map[i][k]);
                continue;
            }

            map[i][k] = new QGraphicsPixmapItem();
            switch (Map_i[i-1][k-1]) {
                case 'X':
                    qDebug() << i*Sources::size << " " << k*Sources::size ;
                    map[i][k]->setPixmap(wall.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    walls.emplace_back(k*Sources::size,i*Sources::size);
                    break;
                case 'K':
                    // TODO jebni kluc
                    continue;
                case '.':
                    map[i][k]->setPixmap(grass.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    break;
                case 'S':
                    player_start = QPoint(k*Sources::size,i*Sources::size);
                    map[i][k]->setPixmap(grass.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    break;
                case 'T':
                    // TODO jebni dvierka
                    break;
                default:
                    qDebug() <<"No match :" << Map_i[i][k];
            }
            map[i][k]->setPos(k*Sources::size, i*Sources::size);
            addItem(map[i][k]);
        }
    }
}


void Game_scene::load_player(){
    player = new Player;
    player->setFocus();
    player->current_position = player_start;
    player->setPos(player_start);
    addItem(player);
}

void Game_scene::move_player(){
    QPoint next_position = player->next_player_position();
    qDebug() <<"Curent : " << next_position;
    for (auto & wall : walls){
        if (next_position.x() < wall.x()){
            if (next_position.x() + Sources::size > wall.x()){
                if (next_position.y() < wall.y()){
                    if (next_position.y() + Sources::size > wall.y()){
                        player->direction = Player::NONE;
                        return;
                    }
                }
                else {
                    if (next_position.y() - Sources::size < wall.y()){
                        player->direction = Player::NONE;
                        return;
                    }
                }
            }
        }
        else {
            if (next_position.x() - Sources::size < wall.x()){
                if (next_position.y() < wall.y()){
                    if (next_position.y() + Sources::size > wall.y()){
                        player->direction = Player::NONE;
                        return;
                    }
                }
                else {
                    if (next_position.y() - Sources::size < wall.y()){
                        player->direction = Player::NONE;
                        return;
                    }
                }
            }
        }
    }

    player->setPos(next_position);
    player->current_position = next_position;
}

