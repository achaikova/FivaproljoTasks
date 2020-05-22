#include "Scene.h"

Scene::Scene(QWidget *parent) {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1250, 700);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);
    resize(1250, 700);
}

Scene::~Scene() {
    setScene(nullptr); //for a faster removal
    scene->clear();
    delete (scene);
}


void Scene::add_background(const QString &image) {
    scene->setBackgroundBrush(QBrush(QImage(image)));
}

void
Scene::add_platform(int x, int y, int amount, const QString &image, int block_width, std::vector<Block *> &platform) {
    for (int i = 0; i < amount; i++) {
        platform.push_back(new Block(QPoint(x + block_width * i, y), image, block_width));
        scene->addItem(platform.back());
    }
}

void Scene::add_players(const std::vector<Player *> &players) {
    for (auto player : players) {
        player->setPos(50, height() - 50 - player->boundingRect().height());
        player->previous_position = player->pos();
        scene->addItem(player);
    }
}

void Scene::addWidget(KeyPresser *pPresser) {
    scene->addWidget((QWidget *) pPresser);
}

void Scene::add_text(QLabel *text) {
    scene->addWidget(text);
}

void Scene::add_button(QPushButton *button) {
    QGraphicsProxyWidget *widgetItem = scene->addWidget(button);
}

void Scene::add_pixmap(QGraphicsPixmapItem *item) {
    scene->addItem(item);
}

void Scene::remove_item(QGraphicsItem *item) {
    scene->removeItem(item);
}

void Scene::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    fitInView(this->sceneRect());
}

void Scene::add_qgrectitem(QGraphicsRectItem *item) {
    scene->addItem(item);
}
