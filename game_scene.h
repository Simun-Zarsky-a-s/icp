//
// Created by samuel on 19.4.2023.
//

#ifndef ICP_GAME_SCENE_H
#define ICP_GAME_SCENE_H

#include <QGraphicsScene>
#include "player.h"
#include "gamemap.h"
#include "Sources.h"

class Game_scene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit Game_scene(QObject *parent);

private:
    ///TODO: TU BUDU funkcie na scenu
    void load_pixmaps();
    void loop();
    void generate_world();
    void load_player();
    void move_player();

    Player* player{};
    QTimer scene_timer;

    QPixmap wall_pixmap;
    QPixmap grass_pixmap;
    QPixmap door_closed_pixmap;
    QPixmap door_open_pixmap;
    QPixmap key_pixmap;

    QGraphicsPixmapItem* map[Sources::MAP_WIDTH][Sources::MAP_HEIGHT]{};
    std::vector<QPoint> walls;
    std::vector<QPoint> keys;
    int number_of_keys;
    QPoint player_start;
    QPoint target;
};

#endif //ICP_GAME_SCENE_H