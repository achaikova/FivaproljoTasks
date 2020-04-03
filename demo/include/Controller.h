#pragma once

#include <vector>
#include <QWidget>
#include <QtGui>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsItem>
#include "Player.h"
#include "Scene.h"
#include "Model.h"
#include "KeyPresser.h"


class Controller : public QObject {
    Q_OBJECT
public:
    Controller();
    void run_game();
public slots:
    void end_game(); // idk what name is needed. depends on further decisions
private:
    std::vector<Player *> players_;
    Scene *scene_;
    Model *model_;
    KeyPresser *key_presser_;
};
