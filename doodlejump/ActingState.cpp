#include "ActingState.h"
#include "config.h"
#include "RandomGenerator.h"
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QGraphicsOpacityEffect>

ActingState::ActingState(QWidget* parent) : QWidget(parent) {

    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(parent->width(), parent->height());

    _backgroundLabel = new QLabel(this);
    QPixmap pixmapBG("D:\\Qt_practice\\doodlejump_sprites\\sprites\\bck.png");
    pixmapBG = pixmapBG.scaled(width(), width() * 1.6, Qt::KeepAspectRatio);
    _backgroundLabel->setGeometry(geometry());
    _backgroundLabel->setPixmap(pixmapBG);
    _backgroundLabel->lower();

    _scoreImage = new QLabel(this);
    QPixmap pixmapScoreImage("D:\\Qt_practice\\doodlejump_sprites\\sprites\\score_background.png");
    pixmapScoreImage = pixmapScoreImage.scaled(width()*1.5, width() * 92 / 60, Qt::IgnoreAspectRatio);
    _scoreImage->setPixmap(pixmapScoreImage);
    _scoreImage->setGeometry(0, 0, width(), width() * 92 / 640);
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(0.7);
    _scoreImage->setGraphicsEffect(opacityEffect);
    _scoreImage->raise();
    
    _scoreText = new QLabel(this);
    _scoreText->setStyleSheet("color: black; font: bold 32px;");
    _scoreText->setFont(QFont("Segoe Print", 12));
    _scoreText->setGeometry(_scoreImage->geometry());
    _scoreText->raise();
    _scoreText->move(_scoreImage->width() * 0.05, _scoreImage->height()* 0.3 - _scoreText->height()/2);
    _scoreText->setText("0");
    _scoreTimer = new QTimer(this);
    connect(_scoreTimer, &QTimer::timeout, this, &ActingState::animateScore);

    _pauseLabel = new QLabel(this);
    QPixmap pixmapPause("D:\\Qt_practice\\doodlejump_sprites\\sprites\\pause-cover@2x.png");
    pixmapPause = pixmapPause.scaled(width() *2, width() * 1.6*2, Qt::IgnoreAspectRatio);
    _pauseLabel->setGeometry(0, -2, width(), width() * 1.6 + 2);
    _pauseLabel->setPixmap(pixmapPause);
    _pauseLabel->hide();

    _mainHero = new MainHero(this);
    connect(_mainHero, &MainHero::intersectionFixed, this, &ActingState::intersectionProcessed);
    connect(_mainHero, &MainHero::gameOverFixed, this, &ActingState::gameOverProcessed);
    connect(_mainHero, &MainHero::gameOverFinished, this, &ActingState::gameOverDecorationsProcessed);
    _mainHero->raise();

    _pauseButton = new QPushButton(this);
    //настсроить кнопку и добавить картинки для паузы
    //тестовый кейс с поджатием ног
    QPixmap pixmapPauseButton("D:\\Qt_practice\\doodlejump_sprites\\sprites\\pause.png");
    pixmapPauseButton = pixmapPauseButton.scaled(width() * 0.08, width() * 0.08, Qt::IgnoreAspectRatio);
    _pauseButton->setGeometry(width() * 0.92, width() * 0.012, width() * 0.08, width() * 0.08);
    _pauseButton->setIcon(QIcon(pixmapPauseButton));
    _pauseButton->setIconSize(_pauseButton->size());
    //_pauseButton->setFlat(true);
    _pauseButton->setStyleSheet("background: transparent; border: none;");
    //_pauseButton->setGraphicsEffect(opacityEffect);
    _pauseButton->raise();
    connect(_pauseButton, &QPushButton::clicked, this, &ActingState::togglePause);
    generateStartPlatfs();

    _jumpDist = parent->height()/2 - 100 - 30 - 27 - 30;
}

void ActingState::update(float deltaTime) {
    if(_isPaused)
        return;
    if(_gameOverAnimationFlag){
        gameOver(deltaTime);
    }
    if(_moveDist > 50){
        //qDebug() << "_MOVEDIST UPDATE" << _moveDist;
        loweringTheScreen(_moveDist, deltaTime);
    }
    if(_gameOverDecorationFlag){
        //_gameOverDecorations->animateShow();
    }
    else{
        _mainHero->update(deltaTime);
    }
    for (auto& platform : _platforms) {
        platform->update(deltaTime);
    }
}

void ActingState::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) {
        _mainHero->setLeftMovement(true);
    }
    if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) {
        _mainHero->setRightMovement(true);
    }
}

void ActingState::keyReleaseEvent(QKeyEvent* event) {
    float deltaTime = 0.016f;
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) {
        _mainHero->setLeftMovement(false);
    }
    if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) {
        _mainHero->setRightMovement(false);
    }
}

void ActingState::generateStartPlatfs(){
    platfGenerator(1, QRect((this->width() - 91) / 2, this->height() - 28, 91, 28), PlatfType::Default);
    platfGenerator(3, QRect(0, -this->height() * 2 / 4, this->width(), this->height() / 4), PlatfType::Default);
    platfGenerator(4, QRect(0, -this->height() / 4, this->width(), this->height() / 4), PlatfType::Default);
    platfGenerator(3, QRect(0, 0, this->width(), this->height() / 4), PlatfType::Default);
    platfGenerator(4, QRect(0, this->height() / 4, this->width(), this->height() / 4), PlatfType::Default);
    platfGenerator(3, QRect(0, this->height() * 2 / 4, this->width(), this->height() / 4), PlatfType::Default);
    platfGenerator(2, QRect(0, this->height() * 3 / 4, this->width(), this->height() / 4), PlatfType::Default);
}

void ActingState::generatePlatfs() {
    int platformCount;
    float movingPlatformProb;

    if (_currentScore < 2000) { //уровень 1
        platformCount = Random::intRand(2, 5);
        movingPlatformProb = 0.1f;
    } else if (_currentScore < 5000) { //уровень 2
        platformCount = Random::intRand(2, 4);
        movingPlatformProb = 0.2f;
    } else if (_currentScore < 10000) { //уровень 3
        platformCount = Random::intRand(2, 3);
        movingPlatformProb = 0.3f;
    } else if (_currentScore < 20000) { //уровень 4
        platformCount = Random::intRand(1, 2);
        movingPlatformProb = 0.5f;
    } else { //уровень 5
        platformCount = 1;
        movingPlatformProb = 0.8f;
    }

    optimalPlatfGenerator(movingPlatformProb);

    if(platformCount > 1) {
        platfGenerator(platformCount - 1, QRect(0, -_generationDist, width(), _generationDist));
    }

}

void ActingState::optimalPlatfGenerator(float movingProb) {
    const int maxHorzJump = 220; // Максимальный горизонтальный прыжок
    const int maxVertJump = _jumpDist; // Максимальный вертикальный прыжок
    const int minGap = 10; // Минимальный отступ

    QRect base = getHighestPlatfCoords();
    int baseX = base.x();
    int baseY = base.y();

    PlatfType type = Random::chance(movingProb) ? PlatfType::Moving : PlatfType::Default;
    int newX, newY;

    if(type == PlatfType::Moving){
        newX = Random::intRand(0, width() - 90);
        newY = baseY - maxVertJump;
    }
    if(type == PlatfType::Default) {
        float angle = Random::doubleRand(M_PI / 4, 3 * M_PI / 4);
        newX = baseX + maxHorzJump * cos(angle);
        newY = baseY - maxVertJump * sin(angle);
        
        // Ограничение границ
        newX = std::clamp(newX, 0, width() - 90);
    }

    //qDebug() << "NEWX" << newX << "NEWY" << newY;

    platfGenerator(1, QRect(newX, newY, 91, 28), type);
}

//переделать кусок экстрапомощи

QRect ActingState::getHighestPlatfCoords() {
    int baseY = height();
    int baseX = 0;
    bool needsExtraHelp = false;

    // Первый проход поиска
    for (auto& platform : _platforms) {
        if (platform && platform->getRect().y() < baseY && platform->getType() != PlatfType::Breaking) {
            baseY = platform->getRect().y();
            baseX = platform->getRect().x();
        }
    }

    // Если нет платформ, добавляем экстренную
    if (baseY > 0) {
        qDebug() << "CALLED EXTRAHELP";
        platfGenerator(1, QRect(0, -29, width(), 28), PlatfType::Default);
        
        // Повторный поиск после генерации
        baseY = height();
        for (auto& platform : _platforms) {
            if (platform && platform->getRect().y() < baseY && platform->getType() != PlatfType::Breaking) {
                baseY = platform->getRect().y();
                baseX = platform->getRect().x();
            }
        }
    }

    return QRect(baseX, baseY, 0, 0);
}

void ActingState::platfGenerator(int count, const QRect& area, std::optional<PlatfType> requiredType) {
    const int platfWidth = 90;
    const int platfHeight = 27;
    const int minDistance = 2;
    const int maxAttempts = 50; // Максимальное количество попыток для MovingPlatform

    std::vector<std::shared_ptr<Platform>> newPlatforms;
    newPlatforms.reserve(count);

    auto intersectsAny = [](const QRect& rect, const auto& platforms) {
        return std::any_of(platforms.begin(), platforms.end(),
            [&rect](const auto& platf) {
                return platf && rect.intersects(platf->getRectForGeneration());
            });
    };

    for (int i = 0; i < count; i++) {
        int x, y;
        bool positionIsFree;
        PlatfType type = requiredType.value_or(static_cast<PlatfType>(Random::intRand(1,3)));
        int attempts = 0;
        
        do {
            // Если не удалось разместить MovingPlatform за maxAttempts попыток - переключаемся на Default
            if (attempts > maxAttempts) {
                positionIsFree = false;
                break;
            }        

            x = Random::intRand(0, area.width() - platfWidth) + area.x();
            y = Random::intRand(0, area.height() - platfHeight) + area.y();
            positionIsFree = true;

            // Замените блок с tempPlatform на:
            QRect checkRect;
            switch(type) {
                case PlatfType::Moving:
                    checkRect = QRect(0, y, width(), 27); // Высота MovingPlatform
                    break;
                case PlatfType::Breaking:
                    checkRect = QRect(x, y, 90, 27);
                    break;
                default:
                    checkRect = QRect(x, y, 90, 27);
            }

            // Проверка пересечений
            if (intersectsAny(checkRect, newPlatforms) || intersectsAny(checkRect, _platforms)) {
                positionIsFree = false;
                attempts++;
                continue;
            }

        } while (!positionIsFree);

        if (positionIsFree) {
            std::shared_ptr<Platform> platform;

            switch (type) {
                case PlatfType::Default:
                    platform = std::make_shared<DefaultPlatform>(x, y, this);
                    break;
                case PlatfType::Breaking:
                    platform = std::make_shared<BreakingPlatform>(x, y, this);
                    break;
                case PlatfType::Moving:
                    platform = std::make_shared<MovingPlatform>(x, y, this);
                    break;
            }

            connect(platform.get(), &Platform::requestedDeletion, 
                   this, &ActingState::deletionProcessed);
            newPlatforms.push_back(platform);
        }
    }

    _platforms.insert(_platforms.end(), newPlatforms.begin(), newPlatforms.end());
    _mainHero->updatePlatforms(_platforms);
    _scoreImage->raise();
    _scoreText->raise();
    _pauseButton->raise();
}

void ActingState::intersectionProcessed(int platformBottom){
    for (auto& platform : _platforms) {
        if (!platform) continue;
        platform->_moveFlag = true;
    }
    _moveDist = (height() - 50) - platformBottom;
    _generationDist = _moveDist;
}

void ActingState::loweringTheScreen(int moveDist, float deltaTime) {
    _allPlatformsStopped = true;
    for (auto& platform : _platforms) {
        if (!platform) continue;
        if (platform->_moveFlag) {
            _allPlatformsStopped = false;
            platform->movingDown(moveDist, deltaTime);
        }
    }
    if (_allPlatformsStopped) {
        addScore(_moveDist);
        _moveDist = 0;
        generatePlatfs();
        _generationDist = 0;
    }
}

void ActingState::deletionProcessed() {
    Platform* platform = qobject_cast<Platform*>(sender());
    if (!platform) return;

    auto it = std::find_if(_platforms.begin(), _platforms.end(),
        [platform](const auto& ptr) { return ptr.get() == platform; }); 
    if (it != _platforms.end()) {
        _platforms.erase(it);
        _mainHero->updatePlatforms(_platforms);
    }
}

void ActingState::animateScore() {
    if(_actualValue < _currentScore) {
        _actualValue++;
        _scoreText->setText(QString::number(_actualValue));
        _scoreText->setStyleSheet("color: black; font: bold 32px;");
    } else {
        _scoreTimer->stop();
        _scoreText->setStyleSheet("color: black; font: bold 26px;");
    }
}

void ActingState::addScore(int points) {
    _currentScore += points;
    if(!_scoreTimer->isActive()) {
        _scoreTimer->start(4);
    }
}


ActingState::~ActingState() {
    //qDebug() << "ActingState destroyed";
    if (_scoreTimer) {
        _scoreTimer->stop();
        delete _scoreTimer;
        _scoreTimer = nullptr;
    }
    delete _mainHero;
}

void ActingState::gameOverProcessed(){
    _gameOverAnimationFlag = true;
    //сделать нормально
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(0.7);
    _pauseButton->setGraphicsEffect(opacityEffect);
    _pauseButton->setEnabled(false);
}

void ActingState::gameOver(float deltaTime){
    if(!_platforms.empty()){
        for (auto& platform : _platforms) {
            if (!platform) continue;
            platform->gameOverMode(deltaTime);
        }
    }
    else if (_gameOverDecorations == nullptr){
        _gameOverDecorations = new GameOverDecorations(this);

        connect(_gameOverDecorations, &GameOverDecorations::playAgainRequested,  this, [this]() { emit restartRequested(); });
        connect(_gameOverDecorations, &GameOverDecorations::menuRequested, this, [this]() { emit returnToMenuRequested(); });
        //connect(_gameOverDecorations, &GameOverDecorations::saveRequested, [this](const QString& name) { emit saveResultRequested(name, _currentScore); });
        
        _gameOverDecorations->animateShow();
        _gameOverDecorations->setScore(_currentScore);
        _mainHero->raise();
        
        _gameOverDecorationFlag = true;
    }
    else if(_gameOverAnimationFlag){
            _mainHero->goOut(deltaTime);
    }
}

void ActingState::gameOverDecorationsProcessed(){
    _gameOverAnimationFlag = false;
}

void ActingState::togglePause() {
    _isPaused = !_isPaused;
    
    if (_isPaused) {
        _pauseButton->setIcon(QIcon("D:\\Qt_practice\\doodlejump_sprites\\sprites\\play@2x.png"));

        _pauseLabel->raise();
        _pauseButton->raise();
        _pauseLabel->show();
    } 
    else {
        _pauseButton->setIcon(QIcon("D:\\Qt_practice\\doodlejump_sprites\\sprites\\pause.png"));
        _pauseLabel->hide();
    }
}