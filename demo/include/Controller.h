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
#include "Utilities.h"

#include "KeyPresser.h"

class Controller : public QObject {
    Q_OBJECT
public:
    //Controller();
    void run_game(); // starts menu (or not - i have no idea)
    void load_player(Player player, Utilities::Color color, QString name_of_image); // will be called from (mouse presser) menu - for now called directly from Controller
    void run_game_match();
    // loads only characters playable from this computer
public slots:
    void end_game(); // idk what name is needed. depends on further decisions
private:
    std::vector<Player *> players_;
    Scene *scene_;
    Model *model_;
    KeyPresser *key_presser_;
};
