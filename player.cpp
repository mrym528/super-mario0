#include "player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QMessageBox>
#include <iostream>

// constructor
Player::Player(int width, int height, Position position, int speed)
    : BodyObject(width, height, position),
    QGraphicsRectItem(position.x, position.y, width, height), speed(speed)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    // Timer for gravity and jumping
    gravityTimer = new QTimer(this);
    connect(gravityTimer, &QTimer::timeout, this, &Player::applyGravity);
    gravityTimer->start(30);
    jumping = false;
    jumpVelocity = -15;
    gravity = 1;
    velocityY = 0;

    qDebug() << "Player initialized at position:" << position.x << position.y;
}
// destructor
Player::~Player()
{
    delete gravityTimer;
}
// draw player  on screen
void Player::draw(QGraphicsScene& scene) const
{
    QGraphicsRectItem* rect = new QGraphicsRectItem(position.x, position.y, width, height);
    QBrush brush(Qt::red);
    rect->setBrush(brush);
    scene.addItem(rect);
}
// handling pressing keys
void Player::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        moveLeft();
        break;
    case Qt::Key_Right:
        moveRight();
        break;
    case Qt::Key_Space:
        if (!jumping) {
            jump();
        }
        break;
    default:
        break;
    }
}

void Player::moveLeft()
{
    position.x -= speed;
    setPos(position.x, position.y);
    qDebug() << "Player moved left to:" << position.x << position.y;
    update();
}

void Player::moveRight()
{
    position.x += speed;
    setPos(position.x, position.y);
    qDebug() << "Player moved right to:" << position.x << position.y;
    update();
}

void Player::jump()
{
    if (!jumping) {
        jumping = true;
        velocityY = jumpVelocity;
        qDebug() << "Player jumped with initial velocity:" << jumpVelocity;
    }
}

void Player::applyGravity()
{
    if (jumping)
    {
        velocityY += gravity;
        position.y += velocityY;
        setPos(position.x, position.y);
        qDebug() << "Applying gravity. VelocityY:" << velocityY << "PositionY:" << position.y;
        if (checkCollisions()) {
            landing();
        } else if (position.y > scene()->height()) {
            emit gameOver();
        }
        update();
    }
}

bool Player::checkCollisions()
{
    if (scene() == nullptr) {
        qDebug() << "Scene is null!";
        return false;
    }

    QList<QGraphicsItem*> items = collidingItems();
    for (QGraphicsItem* item : items)
    {
        Platform* platform = dynamic_cast<Platform*>(item);
        if (platform)
        {
            qDebug() << "Collision detected with platform at position:" << platform->position.x << platform->position.y;
            if (position.y + height <= platform->position.y + platform->height) {
                return true;
            }
        }
    }
    return false;
}

void Player::landing()
{
    jumping = false;
    velocityY = 0;
    QList<QGraphicsItem*> items = collidingItems();
    for (QGraphicsItem* item : items)
    {
        Platform* platform = dynamic_cast<Platform*>(item);
        if (platform)
        {
            position.y = platform->position.y - height;
            setPos(position.x, position.y);
            qDebug() << "Player landed on platform at position:" << position.x << position.y;
        }
    }
    scene()->update();
}