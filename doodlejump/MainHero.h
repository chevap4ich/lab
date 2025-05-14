#ifndef MAIN_HERO
#define MAIN_HERO

#include <QWidget>
#include <vector>
#include <QColor>
#include <QLabel>
#include <QRect>
#include <QString>
#include <QPixmap>
#include <QBitmap>
#include <QKeyEvent>
#include "config.h"
#include "Platform.h"
#include "ActingState.h"
#include <memory>
#include <QPainter>

class ActingState;

class MainHero : public QLabel {
    Q_OBJECT
public:
    MainHero(QWidget* parent);
    ~MainHero(){
        qDebug() << "DELETED MAIN";
    }
    void setLeftMovement(bool);
    void setRightMovement(bool);
    void update(float);
    void setNewPixmap(QString);
    void updatePlatforms(const std::vector<std::shared_ptr<Platform>>&);
    void updatePlatform(const std::shared_ptr<Platform>&);
    void goOut(float);
    void setStartPos(int, int);
    float _velocity, _acceleration;
signals:
    void intersectionFixed(int);
    void gameOverFixed();
    void gameOverFinished();
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    bool _isCentering = false;
    QRect getRect() const;
    int getLineSize() const;
    void checkPlatformCollisions(float&, float&, const float);
    void movingDirectionCheck(float);
    void edgesIntersectionCheck();
    void verticalMovement(float);
    void gameOverCheck(float);
    void setOdskokImage();
    void setNormalImage();
    bool _debug = false;
    QTimer* _odskokTimer;
    int _odskokDuration;
    QWidget* _parent;
    float _x, _y;
    bool _isMoving = true;
    int _lineSize;
    std::vector<std::shared_ptr<Platform>> _platforms = {};
    bool _odskokImage = false;
    bool _movingLeft = false;
    bool _movingRight = false;
    CurrentDirection _currentMoving;    
    float _velocityX = 0.0f;
    float _accelerationX = 75.0f;
    float _maxVelocityX = 75.0f;
    float _friction = 75.0f;
};


#endif // MAIN_HERO