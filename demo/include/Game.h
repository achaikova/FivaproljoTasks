#pragma once

#include <QObject>
#include <QTime>
#include <QTimer>
#include "Controller.h"
#include "Scene.h"

class Game : public QObject {
Q_OBJECT

public:
    Game();
public slots:
    void exitGame();
private slots:
    void init();
private:
    Controller *controller;
    Scene *scene;
};
