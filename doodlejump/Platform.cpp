#include "Platform.h"
#include <QPixmap>

Platform::Platform(int x, int y, PlatfType type, QWidget* parent) : QLabel(parent), _parent(parent), _type(type) {
}

QRect Platform::getRect() const {
    return geometry();
}

QRect Platform::getRectForGeneration() const {
    return geometry();
}

void Platform::movingDown(int moveDist, float deltaTime) {
    if(_finalMove == 0) {
        _finalMove = moveDist;
    }
    float step = deltaTime * _platfVelocity;
    _movedDist += step;
    if(_movedDist < _finalMove) {
        if(!_moveFlag) {
            _moveFlag = true;
        }
        move(x(), y() + step);
    } else {
        move(x(), y() + _finalMove - _movedDist + step);
        _moveFlag = false;
        _movedDist = 0.0f;
        _finalMove = 0;
    }
    if (y() > _parent->height()) {
        emit requestedDeletion();
    }
}

void Platform::gameOverMode(float deltaTime) {
    _platfVelocity = -350.0f;
    float step = deltaTime * _platfVelocity;
    move(x(), y() + step);
    if(y() < 0) {
        emit requestedDeletion();
    }
}

PlatfType Platform::getType() const { 
    return _type; 
};