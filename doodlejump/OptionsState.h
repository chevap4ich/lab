#ifndef OPTIONS_STATE_H
#define OPTIONS_STATE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ButtonForMenu.h"
#include "config.h"

class OptionsState : public QWidget {
    Q_OBJECT
public:
    OptionsState(QWidget* parent = nullptr);
    ~OptionsState() override = default;

signals:
    void returnToMenuRequested(); 

private:
    QLabel* _backgroundLabel;
    QLabel* _optionsTitleLabel;
    ButtonForMenu* _resetScoresButton;
    ButtonForMenu* _scoreMarkersButton;
    ButtonForMenu* _selectBackgroundButton;
    ButtonForMenu* _selectSpriteButton;
    ButtonForMenu* _backButton;

    void setupUI();
};

#endif // OPTIONS_STATE_H