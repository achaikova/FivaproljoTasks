#pragma once

#include <QGraphicsPixmapItem>
#include <queue>
#include <string>
#include <QTimer>
#include "Object.h"

class Block : public QObject, public Object {
    Q_OBJECT
public:
    Block(QPoint position, const QString &name);
    void add_color(Utilities::Color color);
    void change_color(Utilities::Color color);
    void change_color_for_test(Utilities::Color color); // Меняет цвет без анимации. Упрощает тестирование.
    Utilities::Color get_color(){ return color_; };

    size_t get_block_width(){ return block_width; };
    size_t get_block_height(){ return block_height; };

    QRectF boundingRect() const;
			    
public slots:
    void change_color_helper_();

private:
    size_t block_width = 50;
    size_t block_height = 50;

    QTimer *recolor_timer_ = nullptr;
    std::queue<std::string> next_texture_;
    Utilities::Color color_ = Utilities::Color::NONE;
};
