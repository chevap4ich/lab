#include "DefaultPlatform.h"
#include <QPixmap>

DefaultPlatform::DefaultPlatform(int x, int y, QWidget* parent) : Platform(x, y, PlatfType::Default, parent) {
    QPixmap pixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\platform.png");
    setPixmap(pixmap.scaled(90, 27, Qt::KeepAspectRatio));
    setGeometry(x, y, 90, 27);
    show();
}

QRect DefaultPlatform::getRectForGeneration() const {
    return geometry();
}
