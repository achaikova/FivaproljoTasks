#pragma once

#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QAbstractAnimation>
#include <QDebug>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Block.h"
#include "Player.h"
#include "Background.h"
#include "MenuButton.h"

class KeyPresser;

class Scene : public QGraphicsView {
public:
    Scene(QWidget *parent = 0);

    ~Scene() override;

    void add_background(const QString &image);

    /* void View::resizeEvent(QResizeEvent *event) {
         QGraphicsView::resizeEvent(event);
         fitInView(this->sceneRect());
     }*/

    void add_platform(int x, int y, int amount, const QString &image, int block_width,    std::vector<Block *> &platform);

    void add_players(const std::vector<Player *> &players);

    // void add_button(Button *button);

    void add_pixmap(QGraphicsPixmapItem *item);

    void add_button(QPushButton *button);

    void addWidget(KeyPresser *pPresser);

    void add_text(QLabel *text);

    void add_qgrectitem(QGraphicsRectItem *item);

    void remove_item(QGraphicsItem *item);

    int get_width() { return scene->width(); }

    int get_height() { return scene->height(); }

    //void add_item(QGraphicsItem *item);

    void resizeEvent(QResizeEvent *event) override;


    QGraphicsScene *scene;

private:
    Background *background = nullptr;
};
