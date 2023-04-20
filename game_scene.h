//
// Created by samuel on 19.4.2023.
//

#ifndef ICP_GAME_SCENE_H
#define ICP_GAME_SCENE_H

#endif //ICP_GAME_SCENE_H

#include <QGraphicsScene>

class Game_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game_scene(QObject *parent);

private:
    ///TODO: TU BUDU funkcie na scenu
    void loop();
    void generate_world();
    void restart();
};