#ifndef PLAYER_H
#define PLAYER_H

#include "bodyobject.h"
#include "C:/Users/AlborzRayan/CLionProjects/super-mario1/Position.h"
#include "platform.h"
#include "decorator.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <vector>
#include <QObject>   // Ensure QObject is included

class Player : public BodyObject{
    Q_OBJECT

public:
    enum State { StandLeft, StandRight, RunLeft, RunRight, JumpingLeft, JumpingRight };

    Player(int width, int height, Position position, QGraphicsPixmapItem *image = nullptr, int speed = 5);

    void draw(QGraphicsScene& scene) const;
    void setState(State state);
    void handleGravity(std::vector<Platform>& platforms );
    void updatePosition(std::vector<Platform>& platforms);
    void handleMovement();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void updateImage();
    bool isCollidingWithPlatform(std::vector<Platform>& platforms);
private:
    int speed;
    Position velocity;
    State currentState;
    QTimer *movementTimer;
    std::vector<Platform> platforms;
    QPixmap standLeftImage;
    QPixmap standRightImage;
    QPixmap runLeftImage;
    QPixmap runRightImage;
    QPixmap jumpLeftImage;
    QPixmap jumpRightImage;

};

#endif // PLAYER_H
