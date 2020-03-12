#pragma once

#include <vector>
#include <QWidget>
#include <QtGui>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsItem>
#include "Player.h"
#include "Scene.h"

class KeyPresser : public QWidget {
public:
    KeyPresser(Player *player, QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    Player *player_;
};

class Controller {
public:
    Controller();
    void runGame();
private:
    vector<Player> players_;
	Scene *scene_;
	Model *model_;
	KeyPresser *key_presser_;
};
