#ifndef PLATFORM_H
#define PLATFORM_H
#include "position.h"
#include "bodyobject.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Platform : public BodyObject {
public:

    Platform(int width, int height, const Position& position, const QString& imagePath);
    Platform(const Platform& other);
    void draw(QGraphicsScene &scene) const override;

private:
    QString imagePath;
    mutable QGraphicsPixmapItem* image;
};

#endif // PLATFORM_H