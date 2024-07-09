#ifndef PLAYER_H
#define PLAYER_H

#include "bodyobject.h"
#include "position.h"
#include "platform.h"
#include "decorator.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include <vector>
#include <QObject>

class Player : public BodyObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    Player(int width, int height, Position position, int speed);
    ~Player();

    void draw(QGraphicsScene& scene) const;
    void moveLeft();
    void moveRight();
    void jump();
    bool checkCollisions();
    void landing();

protected:
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void applyGravity();

private:
    int speed;
    bool jumping;
    int jumpVelocity;
    int gravity;
    int velocityY;
    QTimer* gravityTimer;

signals:
    void gameOver();
};
#endif // PLAYER_H