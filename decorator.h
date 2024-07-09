#ifndef DECORATOR_H
#define DECORATOR_H

#include "bodyobject.h"
#include "position.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Decorator : public BodyObject {
public:
    Decorator(int width, int height,const Position& position, const QString& imagePath);
    Decorator(const Decorator& other);
    void draw(QGraphicsScene &scene) const override;
private:
    QString imagePath;
    mutable QGraphicsPixmapItem* image;
};

#endif // DECORATOR_H