#include "Scene.h"

Scene::Scene(QWidget *parent) { //TODO - proper coordinates
    game_scene = new QGraphicsScene();
    game_scene->setSceneRect(0, 0, 1250, 700);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(game_scene);
    setFixedSize(1250, 700);
}

Scene::~Scene() {
    setScene(nullptr); //for a faster removal
    game_scene->clear();
    delete (game_scene);
}


void Scene::add_background(const QString &image) {
    game_scene->setBackgroundBrush(QBrush(QImage(image)));
}

void Scene::add_platform(int x, int y, int amount, const QString &image) {
    size_t block_width = 50;
    size_t block_height = 50;
    std::vector<Block *> platform;
    for (int i = 0; i < amount; i++) {
        platform.push_back(new Block(QPoint(x + block_width * i, y), image));
        game_scene->addItem(platform[i]);
    }
}

void Scene::add_players(const std::vector<Player *> &players) {
    for (auto player : players) {
        player->setPos(50, 650 - player->boundingRect().height());
        player->previous_position = player->pos();
        game_scene->addItem(player);
    }
}

void Scene::addWidget(KeyPresser *pPresser) {
    game_scene->addWidget((QWidget *) pPresser);
}

void Scene::add_text(QLabel *text) {
    game_scene->addWidget(text);
}

/*void Scene::add_button(Button *button) {
    game_scene->addItem(button);
}


void Scene::add_item(QGraphicsItem *item) {
    game_scene->addItem(item);
}
*/
void Scene::add_button(QPushButton *button) {
    QGraphicsProxyWidget *widgetItem = game_scene->addWidget(button);
    //button->hide();
}

void Scene::add_pixmap(QGraphicsPixmapItem *item) {
    game_scene->addItem(item);
}