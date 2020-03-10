#ifndef DEMO_DEMO_LEVEL_H
#define DEMO_DEMO_LEVEL_H

#include <QGraphicsScene>
#include <QTimer>
#include <QAbstractAnimation>
#include <QDebug>
#include <Block.h>
#include "Background.h"

class demo_level : public QGraphicsScene {
public:
    explicit demo_level(QObject *parent = 0);

    qreal jumpFactor() const;

    void setJumpFactor(const qreal &jumpFactor);

    void end_level();

protected:
    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

public slots:

    void increase_score(int);

private slots:

    void move_player();

    void jump_player();

    void fall_player();

    void check_timer();

    bool handle_collisions_with_platform();

    QGraphicsItem *colliding_platforms();

    void jump_status_changed(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);


signals:

    void jumpFactorChanged(qreal);

    //void playSound(QString);
    void endLevelOne();

private:
    void initPlayField();

    int velocity;
    qreal ground_level;
    QTimer timer;
    QTimer fall_timer;
    int field_width;

//   Player *m_player;????
    Block *ground;
    Block **platform;

    BackgroundItem *background;
    //  Score *m_score;
};


#endif //DEMO_DEMO_LEVEL_H
