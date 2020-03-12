#ifndef DEMO_MODEL_H
#define DEMO_MODEL_H
#include <QGraphicsPixmapItem>
#include "Player.h"
#include <vector>

class Model : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    void start_game();
private:
    void advance_scene();
    bool game_on;
    QVector<Player *> players_v;
private slots:
    void advance_players();
};

#endif //DEMO_MODEL_H
