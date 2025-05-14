#include "MovingPlatform.h"
#include <QPixmap>
#include <QRandomGenerator>

MovingPlatform::MovingPlatform(int x, int y, QWidget* parent) : Platform(x, y, PlatfType::Moving, parent), _xPos(x) {
    QPixmap pixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\moving_platform.png");
    setPixmap(pixmap.scaled(90, 27, Qt::KeepAspectRatio));
    setGeometry(x, y, 90, 27);
    _velocityX = 50.0f + QRandomGenerator::global()->generateDouble() * 50.0f;
    show();
}

//разобраться с оптимизайией глобально!!!!
void MovingPlatform::update(float deltaTime) {
    _xPos += _moveDirection * _velocityX * deltaTime;

    const float leftBound = 0;
    const float rightBound = _parent->width() - width();

    //углы корректно 
    if (_xPos <= leftBound - 3) {
        _xPos = leftBound;
        _moveDirection = 1;
    } else if (_xPos >= rightBound + 3) {
        _xPos = rightBound;
        _moveDirection = -1;
    }

    move(qRound(_xPos), y());
}

QRect MovingPlatform::getRectForGeneration() const {
    return QRect(0, y(), 470, height());
}
