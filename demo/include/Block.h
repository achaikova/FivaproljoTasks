#pragma once

#include <QGraphicsPixmapItem>
#include <queue>
#include <string>
#include <QTimer>
#include "Object.h"

class Block : public QObject, public Object {
Q_OBJECT
    //  Q_PROPERTY(QRectF rect READ rect WRITE setRect)
public:
    Block(QPoint position, const QString &name);

    Utilities::Color get_color() { return color_; };

    QRectF boundingRect() const;

    void change_color(Utilities::Color color);
    // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    size_t block_width = 50;
    size_t block_height = 50;

public slots:

    void change_color_helper_();

private:
    QTimer *recolor_timer_ = nullptr;
    std::queue<std::string> next_texture_;
    Utilities::Color color_ = Utilities::Color::NONE;
};
