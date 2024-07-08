#include "player.h"
#include <QKeyEvent>
#include "Position.h"
#include "platform.h"
#include "bodyobject.h"
#include <vector>
#include <QObject>   // Ensure QObject is included
#include <QTimer>    // For QTimer
#include <QGraphicsPixmapItem>  // If QGraphicsPixmapItem is used
#include <QString>
#include <iostream>
#include <QBrush>
#include <QGraphicsRectItem>
Player::Player(int width, int height, Position position, QGraphicsPixmapItem *image, int speed)
    : BodyObject(width, height, position, image), speed(speed), currentState(StandRight) {

    // Load images
    standLeftImage = QPixmap(":/spriteStandLeft/assets/spriteStandLeft.png");
    standRightImage = QPixmap(":/spriteStandRight/assets/spriteStandRight.png");
    runLeftImage = QPixmap(":/spriteRunLeft/assets/spriteRunLeft.png");
    runRightImage = QPixmap(":/spriteRunRight/assets/spriteRunRight.png");
    jumpLeftImage = QPixmap(":/spriteStandLeft/assets/spriteStandLeft.png");
    jumpRightImage = QPixmap(":/spriteStandRight/assets/spriteStandRight.png");

    // Set initial image
    //this->image->setPixmap(standRightImage);

    //connect(movementTimer, &QTimer::timeout, this, &Player::updatePosition);
    //QObject::connect(movementTimer, &QTimer::timeout, this, &Player::updatePosition);
    //movementTimer->start(30);
}
void Player::draw(QGraphicsScene& scene){
    QGraphicsRectItem* rect = new QGraphicsRectItem(position.x, position.y, width, height);

    // Set the color to red
    QBrush brush(Qt::red);
    rect->setBrush(brush);

    // Add the rectangle to the scene
    scene.addItem(rect);
}
void Player::setState(State state) {
    //if (currentState != state) {
        //currentState = state;
        //updateImage();
    //}
    currentState = state;
}

void Player::updateImage() {
    //switch (currentState) {
    //case StandLeft:
        //image->setPixmap(standLeftImage);
        //break;
    //case StandRight:
        //image->setPixmap(standRightImage);
        //break;
    //case RunLeft:
        /*image->setPixmap(runLeftImage);
        break;
    case RunRight:
        image->setPixmap(runRightImage);
        break;
    case JumpingLeft:
        image->setPixmap(jumpLeftImage);
        break;
    case JumpingRight:
        image->setPixmap(jumpRightImage);
        break;
    }*/

}

void Player::handleGravity(std::vector<Platform>& platforms) {
    bool onPlatform = false;

    for (const auto& platform : platforms) {
        if (isCollidingWithPlatform(platforms)) {  // Pass entire platforms vector here
            onPlatform = true;
            position.y = platform.position.y - height;
            velocity.y = 0;
            break;
        }
    }

    if (!onPlatform) {
        velocity.y += 1; // Simple gravity increment
        position.y += velocity.y;
        if (position.y > 350) { // Ground level
            position.y = 350;
            velocity.y = 0;
        }
    }
}

void Player::handleMovement() {
    if (currentState == RunLeft || currentState == JumpingLeft) {
        position.x = position.x - speed;
    } else if (currentState == RunRight || currentState == JumpingRight) {
        position.x = position.x + speed;
    }
    image->setPos(position.x, position.y);
}

void Player::updatePosition(std::vector<Platform>& platforms) {
    handleMovement();
    handleGravity(platforms);
}

void Player::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        if (currentState == StandLeft || currentState == RunRight || currentState == StandRight || velocity.y == 0) {
            setState(RunLeft);
        } else if (currentState == JumpingRight || currentState == JumpingLeft) {
            setState(JumpingLeft);
        }
        break;
    case Qt::Key_Right:
        if (currentState == StandRight || currentState == RunLeft || currentState == StandLeft || velocity.y == 0) {
            setState(RunRight);
        } else if (currentState == JumpingRight || currentState == JumpingLeft) {
            setState(JumpingRight);
        }
        break;
    case Qt::Key_Space:
        if (velocity.y == 0) {
            velocity.y = -15; // Jumping velocity
            if (currentState == RunLeft || currentState == StandLeft) {
                setState(JumpingLeft);
            } else if (currentState == RunRight || currentState == StandRight) {
                setState(JumpingRight);
            }
        }
        break;
    default:
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        if (currentState == RunLeft) setState(StandLeft);
        break;
    case Qt::Key_Right:
        if (currentState == RunRight) setState(StandRight);
        break;
    default:
        break;
    }
}

bool Player::isCollidingWithPlatform(std::vector<Platform>& platforms) {
    for (auto& p : platforms) {
        QRectF platformRect(p.position.x, p.position.y, p.width, p.height);
        QRectF playerRect(position.x, position.y, width, height);

        if (playerRect.intersects(platformRect)) {
            return true;
        }
    }
    return false;
}
