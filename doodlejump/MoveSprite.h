#ifndef MOVE_SPRITE_H
#define MOVE_SPRITE_H

#include <QLabel>
#include <QPixmap>
#include <QRect>
#include <QRandomGenerator>
#include <QtMath>
#include "config.h"

class MoveSprite : public QLabel {
    Q_OBJECT
public:
    MoveSprite(QWidget*);
    double _speed;  
    virtual ~MoveSprite() = default;
    void setImage(const QString&);
    void updatePosition(float);
private:
    double _startX, _startY;
    //double _speed;    
    double _amplitude;
    double _frequency;
    double _phase = 0;       
};

#endif // MOVE_SPRITE_H