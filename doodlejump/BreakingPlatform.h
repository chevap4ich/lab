#ifndef BREAKING_PLATFORM_H
#define BREAKING_PLATFORM_H

#include "Platform.h"
#include "config.h"

class BreakingPlatform : public Platform {
    Q_OBJECT
public:
    BreakingPlatform(int x, int y, QWidget* parent = nullptr);
    QRect getRectForGeneration() const override;
    void breakdown() override;
private:
    bool _isBreaking = false;
    QTimer* _breakTimer = nullptr;
};

#endif // BREAKING_PLATFORM_H