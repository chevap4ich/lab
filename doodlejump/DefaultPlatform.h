#ifndef DEFAULT_PLATFORM_H
#define DEFAULT_PLATFORM_H

#include "Platform.h"
#include "config.h"

class DefaultPlatform : public Platform {
    Q_OBJECT
public:
    DefaultPlatform(int x, int y, QWidget* parent = nullptr);
    QRect getRectForGeneration() const override;
};

#endif // DEFAULT_PLATFORM_H