#ifndef BODYOBJECT_H
#define BODYOBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include "Position.h"

class BodyObject:public QObject {
    Q_OBJECT
public:
    int width;
    int height;
    Position position;
    QGraphicsPixmapItem* image;

    BodyObject(int width, int height, Position position, QGraphicsPixmapItem* image = nullptr);
    ~BodyObject();
    BodyObject(const BodyObject& other);

    virtual void draw(QGraphicsScene& scene) = 0;
};

#endif // BODYOBJECT_H
