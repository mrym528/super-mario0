#include "bodyobject.h"
//constructor
BodyObject::BodyObject(int width, int height, Position position, QGraphicsPixmapItem* image)
    : width(width), height(height), position(position), image(image) {}
//destructor
BodyObject::~BodyObject() {
    delete image;
}
//copy constructor
BodyObject::BodyObject(const BodyObject& other)
    : QObject(other.parent()),
    width(other.width),
    height(other.height),
    position(other.position),
    image(other.image){}