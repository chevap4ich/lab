#ifndef MENU_STATE
#define MENU_STATE

#include <QWidget>
#include <QLabel>
#include <memory>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include "MoveSprite.h"
#include "ButtonForMenu.h"
#include "config.h"

class MenuState : public QWidget {
    Q_OBJECT
public:
    MenuState(QWidget* = nullptr);
    void update(float);
signals:
    void playRequested();
    void exitRequested();
    void moveLeft();
    void moveRight();
    void highScoresRequested();
    void optionsRequested();
private:
    void createSprites();
    ButtonForMenu* _playButton;
    ButtonForMenu* _highScoresButton;
    ButtonForMenu* _optionsButton;
    ButtonForMenu* _exitButton;
    std::vector<std::unique_ptr<MoveSprite>> _sprites;
};

#endif // MENU_STATE