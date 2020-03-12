#ifndef DEMO_DEMOPLAYER_H
#define DEMO_DEMOPLAYER_H

#include "Entity.h"
#include <QPoint>

class DemoPlayer : public Entity {

public:

    DemoPlayer(QPoint position);

    void setRunning(bool _running);

    // pure virtual methods that must be implemented
    virtual std::string& name() = 0;

    virtual void animate() = 0;

    virtual void hit(Object *what, Direction fromDir) = 0;

    // override die method so we can play Mario death animation
    virtual void die() = 0;

    // jump
    void jump();
};


#endif //DEMO_DEMOPLAYER_H
