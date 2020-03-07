#pragma once

#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>


class Player : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void fall_down();
};
