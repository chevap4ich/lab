#ifndef GAME_OVER_DECORATIONS
#define GAME_OVER_DECORATIONS

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QCloseEvent>
#include <QLineEdit>
#include <QLabel>
#include "ButtonForMenu.h"

class GameOverDecorations : public QWidget {
    Q_OBJECT
public:
    GameOverDecorations(QWidget* parent = nullptr);
    
    void animateShow();
    void setScore(int score);

signals:
    //void saveRequested(const QString& name);
    void playAgainRequested();
    void menuRequested();

private:
    QLabel* _scoreLabel;
    QLineEdit* _nameEdit;
    ButtonForMenu* _saveButton;
    ButtonForMenu* _playAgainButton;
    ButtonForMenu* _menuButton;
    QPropertyAnimation* _animation;
};

#endif //GAME_OVER_DECORATIONS