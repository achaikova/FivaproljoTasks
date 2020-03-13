#ifndef DEMO_MODEL_H
#define DEMO_MODEL_H

#include <QGraphicsPixmapItem>
#include "Scene.h"
#include "Player.h"
#include <vector>

class Model : public QObject {
//    Q_OBJECT
public:
    Model() = delete;

	explicit Model(std::vector<Player*>& players);

	void make_new_level(Scene *gs);

    void advance_players();

    void advance_scene();
private:
    bool game_on;
    Scene *game_scene;
	std::vector<Player *> players_;
};

#endif //DEMO_MODEL_H
