#include "platform.h"
#include "bodyobject.h"
#include "Position.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>

Platform::Platform(int width, int height, const Position& position, const QString& imagePath)
    : BodyObject(width, height, position, image), imagePath(imagePath) {}
void Platform::draw(QGraphicsScene &scene) const {
    /*if (!image) {
        image = new QGraphicsPixmapItem(QPixmap(imagePath));
    }*/
    image->setPos(position.x, position.y);
    scene.addItem(image);
}
Platform::Platform(const Platform& other)
    : BodyObject(other),            // Initialize base class copy constructor
    imagePath(other.imagePath){}
