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
    setSceneRect(0,0, Gamemap::MAP_WIDTH, Gamemap::MAP_HEIGHT);
    generate_world();
    load_player();
    loop();
}

void Game_scene::loop() {

}

void Game_scene::generate_world() {
    std::vector<std::vector <char>> Map_i = {
            {'X', '.', 'X'},
            {'.', '.', 'X'},
            {'X', '.', 'X'}
    };

    QPixmap wall("/home/samuel/Desktop/BIT/ICP/Projekt/icp/content/wall.jpg");
    QPixmap grass("/home/samuel/Desktop/BIT/ICP/Projekt/icp/content/grass.png");

    for (int i=0; i < Gamemap::MAP_WIDTH; i++){
        for (int k=0; k < Gamemap::MAP_HEIGHT; k++){
            map[i][k] = new QGraphicsPixmapItem();
            switch (Map_i[i][k]) {
                case 'X':
                    map[i][k]->setPixmap(wall.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    break;
                case 'K':
                    // TODO jebni kluc
                    continue;
                case '.':
                    map[i][k]->setPixmap(grass.scaled(Sources::size, Sources::size, Qt::KeepAspectRatio));
                    break;
                case 'T':
                    // TODO jebni dvierka
                    break;
                default:
                    qDebug() <<"No match :" << Map_i[i][k];
            }
            map[i][k]->setPos(i*Sources::size, k*Sources::size);
            addItem(map[i][k]);
        }
    }
}


void Game_scene::load_player(){
    player = new Player;
    player->setFocus();
    player->setPos(0,0);
    addItem(player);
}