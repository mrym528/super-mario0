#include "bodyobject.h"

BodyObject::BodyObject(int width, int height, Position position, QGraphicsPixmapItem *image)
    : width(width), height(height), position(position), image(image) {
    if (!image) {
        this->image = new QGraphicsPixmapItem();
    }
}
BodyObject::~BodyObject() {
    delete image;
}
BodyObject::BodyObject(const BodyObject& other)
    : QObject(other.parent()),   // Initialize QObject base class (if applicable)
    width(other.width),        // Copy member variables
    height(other.height),
    position(other.position),
    image(other.image){} // Deep copy QGraphicsPixmapItem
