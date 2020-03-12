#include <QWidget>
#include <QtGui>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsItem>

class Controller : public QWidget {
    Q_OBJECT
public:
    Controller(Player *player, QWidget *parent = 0);
	
protected:
    void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
private:
	Player *player;
};
