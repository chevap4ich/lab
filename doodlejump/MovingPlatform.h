#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H

#include "Platform.h"
#include "config.h"

class MovingPlatform : public Platform {
    Q_OBJECT
public:
    MovingPlatform(int x, int y, QWidget* parent = nullptr);
    QRect getRectForGeneration() const override;
    void update(float) override;
private:
    float _xPos;
    float _velocityX;
    int _moveDirection = 1;
};

#endif // MOVING_PLATFORM_H