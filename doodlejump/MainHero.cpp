#include "MainHero.h"

MainHero::MainHero(QWidget* parent) : QLabel(parent) {
    _parent = parent;
    setFixedSize(62, 60);
    _velocity = 0;
    _acceleration = 50;
    _x = (parent->width() - width()) / 2;
    _y = parent->height() / 2; // Центрировать по вертикали
    _lineSize = 1;
    QPixmap spritePixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\blue-lik-left@2x.png");
    spritePixmap = spritePixmap.scaled(width() * 2, height() * 2, Qt::KeepAspectRatio);
    setPixmap(spritePixmap);
    _odskokTimer = new QTimer(this);
    _odskokTimer->setSingleShot(true);
    connect(_odskokTimer, &QTimer::timeout, this, &MainHero::setNormalImage);
    _odskokDuration = 400;
    _currentMoving = CurrentDirection::Left;
}

void MainHero::setStartPos(int x, int y){
    _x = x, 
    _y = y;
}

void MainHero::setNewPixmap(QString filepath) {
    QPixmap spritePixmap(filepath);
    spritePixmap = spritePixmap.scaled(width() * 2, height() * 2, Qt::KeepAspectRatio);
    setPixmap(spritePixmap);
    
}

QRect MainHero::getRect() const { 
    return QRect(_x + width() / 8, _y + height() / 8, width() * 3 / 4, height() * 7 / 8); 
}

int MainHero::getLineSize() const { 
    return _lineSize * 2; 
}

void MainHero::update(float deltaTime){
    gameOverCheck(deltaTime);
    movingDirectionCheck(deltaTime);
    verticalMovement(deltaTime);
    edgesIntersectionCheck();
    move(static_cast<int>(_x), static_cast<int>(_y));
}

void MainHero::checkPlatformCollisions(float& newY, float& newVelocity, const float deltaTime) {
    QRect heroRect = getRect();

    auto platformsCopy = _platforms;
    for (auto& platform : platformsCopy) {
        if (!platform) continue;
        QRect platformRect = platform->getRect();
        if (_velocity > 0 &&
            newY + height() >= platformRect.top() && 
            newY + height() <= platformRect.bottom() &&
            heroRect.right() > platformRect.left() &&
            heroRect.left() < platformRect.right() && 
            platform->getType() == PlatfType::Breaking){
                platform->breakdown();
            }
        if (_velocity > 45 &&
            newY + height() >= platformRect.top() + 7 && 
            newY + height() <= platformRect.top() + 12 &&
            heroRect.right() > platformRect.left() &&
            heroRect.left() < platformRect.right() &&
            platform->getType() != PlatfType::Breaking){
            float len = platformRect.y() - _y - height();
            float deltaTimeDown = (-_velocity + sqrt(_velocity*_velocity + 2*_acceleration*len)) / _acceleration;
            float deltaTimeUp = deltaTime - deltaTimeDown;

            float bottomVelocity = _velocity + _acceleration*deltaTimeDown;
            bottomVelocity = -bottomVelocity;
            //bottomVelocity *= 0.4f;

            newY = float(platformRect.y() - height()) + bottomVelocity*deltaTimeUp + _acceleration*deltaTimeUp*deltaTimeUp/2;

            newVelocity = bottomVelocity + _acceleration*deltaTimeUp;

            emit intersectionFixed(platformRect.bottom());

            setOdskokImage();
        }
    }
}

void MainHero::updatePlatforms(const std::vector<std::shared_ptr<Platform>>& platforms) {
    _platforms = platforms;
    raise();
}

void MainHero::updatePlatform(const std::shared_ptr<Platform>& platform) {
    _platforms.push_back(platform);
    raise();
}

void MainHero::setLeftMovement(bool cond){
    if(_movingLeft != cond)
        _movingLeft = cond;
}

void MainHero::setRightMovement(bool cond){
    if(_movingRight != cond)
        _movingRight = cond;
}

void MainHero::setOdskokImage(){
    if(!_odskokImage){
        if(_currentMoving == CurrentDirection::Left){
            setNewPixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\blue-lik-left-odskok@2x.png");
        }
        else if(_currentMoving == CurrentDirection::Right){
            setNewPixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\blue-lik-right-odskok@2x.png");
        }
        _odskokImage = true;
        _odskokTimer->start(_odskokDuration);
    }
}

void MainHero::setNormalImage(){
    if(_odskokImage){
        if(_currentMoving == CurrentDirection::Left){
            setNewPixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\blue-lik-left@2x.png");
        }
        else if(_currentMoving == CurrentDirection::Right){
            setNewPixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\blue-lik-right@2x.png");
        }
        _odskokImage = false;
    }
}
//приоритет последнего направления
void MainHero::movingDirectionCheck(float deltaTime) {
    if (!_movingLeft && !_movingRight) {
        if (_velocityX > 0) {
            _velocityX = std::max(0.0f, _velocityX - _friction * deltaTime);
        } else if (_velocityX < 0) {
            _velocityX = std::min(0.0f, _velocityX + _friction * deltaTime);
        }
    }
    else {
        if (_movingLeft) {
            _velocityX = std::max(-_maxVelocityX, _velocityX - _accelerationX * deltaTime);
            if(_currentMoving != CurrentDirection::Left) {
                _odskokImage ? setNewPixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\blue-lik-left-odskok@2x.png")
                             : setNewPixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\blue-lik-left@2x.png");
                _currentMoving = CurrentDirection::Left;
            }
        }
        if (_movingRight) {
            _velocityX = std::min(_maxVelocityX, _velocityX + _accelerationX * deltaTime);
            if(_currentMoving != CurrentDirection::Right) {
                _odskokImage ? setNewPixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\blue-lik-right-odskok@2x.png")
                             : setNewPixmap("D:\\Qt_practice\\doodlejump_sprites\\sprites\\blue-lik-right@2x.png");
                _currentMoving = CurrentDirection::Right;
            }
        }
    }

    _x += _velocityX * deltaTime;

    if ((_movingLeft && _velocityX > 0) || (_movingRight && _velocityX < 0)) {
        _velocityX *= 0.9f;
    }
}

void MainHero::edgesIntersectionCheck(){
    if (_x < -width() / 2) {
        _x = _parent->width() - width() / 2;
    }
    else if (_x > _parent->width() - width() / 2) {
        _x = -width() / 2;
    }
}

void MainHero::verticalMovement(float deltaTime){
    if(_isMoving){
        float newY = _y + _velocity*deltaTime + _acceleration*deltaTime*deltaTime/2;
        float newVelocity = _velocity + _acceleration*deltaTime;
        checkPlatformCollisions(newY, newVelocity, deltaTime);
        
        _y = newY;
        _velocity = newVelocity;
    
        if (_y != _y || _velocity != _velocity){
            _isMoving = false;
            _y = _parent->height() - height();
            _velocity = 0;
            _acceleration = 0;
        }
    }
}

void MainHero::paintEvent(QPaintEvent* event) {
    QLabel::paintEvent(event); 
    if (_debug) {
        QPainter painter(this);
        painter.setBrush(QColor(0, 0, 255, 50));
        painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
        painter.drawRect(0, 0, width(), height());
        
        painter.setBrush(Qt::NoBrush);
        painter.setPen(Qt::green);
        painter.drawRect(getRect().translated(-geometry().topLeft()));
    }
}

void MainHero::gameOverCheck(float deltaTime){
    if(_y > _parent->height() - height()){
        emit gameOverFixed();
        _isMoving = false;
    }
}
//поиграть с мэджик намберами
void MainHero::goOut(float deltaTime) {
    if (!_isMoving) {
        _isMoving = true;
        _isCentering = true;
        _velocity = -150;
        _acceleration = -50;
    }
    float targetY = _parent->height() * 0.15;
    if (_isCentering) {
        if (_y < (_parent->height() - targetY) / 2) {
            _acceleration = 60;
        }
        if (_y < targetY) {
            _y = targetY;
            _isCentering = false;
            _velocity = 30;
            _acceleration = 100;
        }
    }
    //qDebug() << _y << targetY << _velocity;
    _y += _velocity * deltaTime;
    _velocity += _acceleration * deltaTime;
    move(static_cast<int>(_x), static_cast<int>(_y));

}