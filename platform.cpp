#include "platform.h"
#include "bodyobject.h"
#include "position.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>

//constructor
Platform::Platform(int width, int height, const Position& position, const QString& imagePath)
    : BodyObject(width, height, position), imagePath(imagePath) {}
//copy constructor
Platform::Platform(const Platform& other)
    : BodyObject(other),
    imagePath(other.imagePath), image(nullptr){}
//draw platform on screen
void Platform::draw(QGraphicsScene &scene) const {
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