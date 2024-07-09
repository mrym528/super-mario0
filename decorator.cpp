#include "decorator.h"
#include "position.h"
#include "bodyobject.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>

// constructor
Decorator::Decorator(int width, int height, const Position &position, const QString &imagePath)
    : BodyObject(width, height, position), imagePath(imagePath) {}
// copy constructor
Decorator::Decorator(const Decorator& other)
    : BodyObject(other), imagePath(other.imagePath), image(nullptr){}
// draw decoration on screen
void Decorator::draw(QGraphicsScene &scene) const{
    if (!image) {
        QPixmap pixmap(imagePath);
        if (pixmap.isNull()) {
            qDebug() << "Error loading image at path:" << imagePath;
            return;
        }
        image = scene.addPixmap(pixmap);
        qDebug() << "Image loaded successfully from path:" << imagePath;
    }
    image->setPos(position.x, position.y);
}