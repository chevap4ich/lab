#ifndef PLATFORM_H
#define PLATFORM_H

#include <QLabel>
#include <QTimer>
#include "config.h"


class Platform : public QLabel {
    Q_OBJECT
public:
    Platform(int x, int y, PlatfType type, QWidget* parent = nullptr);
    virtual ~Platform() = default;
    QRect getRect() const;
    virtual QRect getRectForGeneration() const;
    virtual void movingDown(int moveDist, float deltaTime);
    virtual void gameOverMode(float deltaTime);
    virtual void breakdown() {}
    virtual void update(float) {}
    virtual PlatfType getType() const;

    float _movedDist = 0.0f;
    bool _moveFlag = false;

signals:
    void requestedDeletion();

protected:
    QWidget* _parent;
    float _platfVelocity = 250.0f;
    float _acceleration;
    int _finalMove = 0;
    PlatfType _type;
};

#endif // PLATFORM_H