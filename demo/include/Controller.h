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

class KeyPresser : public QWidget {
public:
    explicit KeyPresser(Player *player, QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    Player *player_;
};

class Controller {
public:
    Controller();
    void runGame();
private:
    std::vector<Player *> players_;
	Scene *scene_;
	Model *model_;
	KeyPresser *key_presser_;
};
