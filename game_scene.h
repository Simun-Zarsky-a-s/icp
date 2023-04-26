//
// Created by samuel on 19.4.2023.
//

#ifndef ICP_GAME_SCENE_H
#define ICP_GAME_SCENE_H

#include <QGraphicsScene>
#include "player.h"
#include "gamemap.h"
#include "Sources.h"
#include "ghost.h"

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
    void load_ghost(QPoint position);
    static bool check_intersection(QPoint first, QPoint second);
    void check_for_keys();
    void check_for_ghosts();

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
    std::vector<Ghost*> ghosts;
    QPoint player_start;
    QPoint target;
    bool door_open;


};

#endif //ICP_GAME_SCENE_H