//
// Created by samuel on 19.4.2023.
//

#ifndef ICP_GAME_VIEW_H
#define ICP_GAME_VIEW_H

#endif //ICP_GAME_VIEW_H

#include <QGraphicsView>
#include "game_scene.h"

class Game_view : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Game_view();

private:
    Game_scene *game_scene;

protected:
    virtual void KeyPressEvent(QKeyEvent *event) override;
};