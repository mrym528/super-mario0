#ifndef DECORATOR_H
#define DECORATOR_H

#include "bodyobject.h"
#include "Position.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Decorator : public BodyObject {
public:
    Decorator(int width, int height,const Position& position, const QString& imagePath);

    void draw(QGraphicsScene &scene) override;
    Decorator(const Decorator& other);
private:
    QString imagePath;
};

#endif // DECORATOR_H
