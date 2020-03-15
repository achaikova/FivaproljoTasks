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
    enum { Type = UserType + 1 };
    int type() const;
    void add_color(int color);
    QRectF boundingRect() const;
    
    void change_color(int color);
    // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
    size_t block_width = 50;
    size_t block_height = 50;
			    
public slots:
    void change_color_();
      
private:
    QTimer *recolor_timer_ = nullptr;
    std::queue<std::string> next_texture_;
    int color_ = 0; // TODO enum
};
