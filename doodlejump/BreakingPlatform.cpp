#include "BreakingPlatform.h"
#include <QPixmap>

BreakingPlatform::BreakingPlatform(int x, int y, QWidget* parent) : Platform(x, y, PlatfType::Breaking, parent) {
    QPixmap pixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\breaking_platform1.png");
    setPixmap(pixmap.scaled(90, 27, Qt::KeepAspectRatio));
    setGeometry(x, y, 90, 27);
    show();
}

void BreakingPlatform::breakdown() {
    if (_isBreaking) 
        return;
    _isBreaking = true;
    
    resize(90, 50);
    QPixmap pixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\breaking_platform2.png");
    setPixmap(pixmap.scaled(90, 50, Qt::KeepAspectRatio));
    
    _breakTimer = new QTimer(this);
    connect(_breakTimer, &QTimer::timeout, [this]() {
        this->movingDown(_parent->height() - y() + 1, 0.05f);
    });
    _breakTimer->start(16);
}

QRect BreakingPlatform::getRectForGeneration() const {
    return geometry();
}