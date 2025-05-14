#ifndef ACTINGSTATE_H
#define ACTINGSTATE_H

#include <QWidget>
#include <vector>
#include <QColor>
#include <QTimer>
#include <QLabel>
#include <QRect>
#include <QPixmap>
#include <QKeyEvent>
#include "config.h"
#include <QList>
#include <QPointer>
#include "MainHero.h"
#include "Platform.h"
#include "DefaultPlatform.h"
#include "BreakingPlatform.h"
#include "MovingPlatform.h"
#include "GameOverDecorations.h"
#include <memory>
#include <vector>

class MainHero;

class ActingState : public QWidget {
    Q_OBJECT
public:
    QLabel* _platform;
    ActingState(QWidget* parent = nullptr);
    ~ActingState();
    void update(float deltaTime);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void platfGenerator(int, const QRect&, std::optional<PlatfType> = std::nullopt);
    void loweringTheScreen(int, float);
    int _moveDist = 0;
    int _generationDist = 0;
signals:
    void restartRequested();
    void returnToMenuRequested();
    void saveResultRequested(const QString& name, int score);
private slots:
    void intersectionProcessed(int);
    void deletionProcessed();
    void gameOverProcessed();
    void gameOverDecorationsProcessed();
    void togglePause();
private:
    QWidget* _parent;
    QLabel* _scoreText;
    int _currentScore = 0;
    int _actualValue = 0;
    int _jumpDist;
    QTimer* _scoreTimer;
    QLabel* _backgroundLabel;
    QLabel* _pauseLabel;
    QLabel* _scoreImage;
    QPushButton* _pauseButton;
    GameOverDecorations* _gameOverDecorations = nullptr;
    MainHero* _mainHero;
    bool _isPaused = false;
    bool _allPlatformsStopped;
    bool _gameOverAnimationFlag = false;
    bool _gameOverDecorationFlag = false;
    std::vector<std::shared_ptr<Platform>> _platforms;
    void gameOver(float);
    void animateScore();
    void addScore(int);
    void generateStartPlatfs();
    void generatePlatfs();
    void optimalPlatfGenerator(float);
    QRect getHighestPlatfCoords();
};

#endif // ACTINGSTATE_H