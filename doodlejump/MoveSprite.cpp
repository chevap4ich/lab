#include "MoveSprite.h"

MoveSprite::MoveSprite(QWidget* parent) : QLabel(parent)
{
    double _startX = QRandomGenerator::global()->bounded(-width(), parent->width());
    double _startY = QRandomGenerator::global()->bounded(int(parent->height() * 0.28), int(parent->height() * 0.67));
    move(_startX, _startY);
    _speed = QRandomGenerator::global()->bounded(2) ? QRandomGenerator::global()->bounded(120, 201)
        : QRandomGenerator::global()->bounded(-200, -119);
    _amplitude = 20.0 + QRandomGenerator::global()->generateDouble() * 25.0;
    _frequency = 1.0;
}

void MoveSprite::updatePosition(float deltaTime) {
    //TODO перевести правильно на double
    _startX += _speed * double(deltaTime);
    _phase += _frequency * double(deltaTime);
    double currentY = _startY + (_amplitude * std::sin(_phase));

    QRect parentRect = parentWidget()->rect();

    if (_startX < -width()) {
        _startX = parentRect.width();
        _startY = QRandomGenerator::global()->bounded(int(parentRect.height() * 0.28), int(parentRect.height() - (parentRect.height() * 0.33)));
    }
    else if (_startX > parentRect.width()) {
        _startX = -width();
        _startY = QRandomGenerator::global()->bounded(int(parentRect.height() * 0.28), int(parentRect.height() - (parentRect.height() * 0.33)));
    }

    move(static_cast<int>(std::round(_startX)), static_cast<int>(std::round(currentY)));
}


void MoveSprite::setImage(const QString &imagePath) {
    QPixmap spritePixmap(imagePath);
    spritePixmap = spritePixmap.scaled(SCREEN_SIZE_X / 6, SCREEN_SIZE_Y / 6, Qt::KeepAspectRatio);
    setPixmap(spritePixmap);
    resize(spritePixmap.size());
}