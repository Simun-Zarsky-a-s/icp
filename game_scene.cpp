//
// Created by samuel on 19.4.2023.
//
#include <QGraphicsPixmapItem>
#include "game_scene.h"


Game_scene ::Game_scene(QObject *parent) : QGraphicsScene{parent}{

}

void Game_scene::loop() {

}

void Game_scene::generate_world() {
    for (int i; i < Gamemap::MAP_WIDTH; i++){
        for (int k; k < Gamemap::MAP_HEIGHT; k++){
            switch(Sources::Map[i,k]){
                case 'X':
                    Q
            }
        }
    }
}

void Game_scene::restart(){

}

void Game_scene::load_player(){
    pixelMap.load("content/pacman.png");
}