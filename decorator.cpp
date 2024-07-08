#include "decorator.h"
#include "Position.h"
#include "bodyobject.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>

Decorator::Decorator(int width, int height, const Position &position, const QString &imagePath)
    : BodyObject(width, height, position, image), imagePath(imagePath) {}

void Decorator::draw(QGraphicsScene &scene) const{
    /*if (!image) {
        image = new QGraphicsPixmapItem(QPixmap(imagePath));
    }*/
    image->setPos(position.x, position.y);
    scene.addItem(image);
}
Decorator::Decorator(const Decorator& other)
    : BodyObject(other), imagePath(other.imagePath){}
