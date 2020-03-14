#ifndef DEMO_BLOCK_H
#define DEMO_BLOCK_H

#include <QGraphicsPixmapItem>
#include "Object.h"

class Block :  public Object {
 //   Q_OBJECT
  //  Q_PROPERTY(QRectF rect READ rect WRITE setRect)
public:
    Block(QPoint position, const QString &name);
    enum { Type = UserType + 1 };
    int type() const;
    void add_color(int color);
    QRectF boundingRect() const;
   // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    size_t block_width = 50;
    size_t block_height = 50;
};

#endif //DEMO_BLOCK_H
