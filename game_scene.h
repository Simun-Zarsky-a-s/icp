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
    void loop();
    void generate_world();
    void load_player();
    void move_player();

    QPixmap pixelMap;
    Player* player{};
    QTimer scene_timer;

    QGraphicsPixmapItem* map[Sources::MAP_WIDTH][Sources::MAP_HEIGHT]{};
    std::vector<QPoint> walls;
    QPoint player_start;
};

#endif //ICP_GAME_SCENE_H