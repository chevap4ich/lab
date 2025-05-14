#include "OptionsState.h"
#include <QPixmap>
#include <QFont>

OptionsState::OptionsState(QWidget* parent) : QWidget(parent) {
    setFixedSize(parent->width(), parent->height());
    setupUI();

    // Load background image
    _backgroundLabel = new QLabel(this);
    QPixmap pixmapBG("D:/Qt_practice/doodlejump_sprites/sprites/bck.png"); // Replace with your path
    pixmapBG = pixmapBG.scaled(width(), width() * 1.6, Qt::KeepAspectRatio);
    _backgroundLabel->setGeometry(geometry());
    _backgroundLabel->setPixmap(pixmapBG);
    _backgroundLabel->lower();
}

void OptionsState::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Options title
    _optionsTitleLabel = new QLabel("Options", this);
    _optionsTitleLabel->setStyleSheet("color: black; font: bold 64px;");
    _optionsTitleLabel->setFont(QFont("Segoe Print", 64, QFont::Bold));
    _optionsTitleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(_optionsTitleLabel);

    // Buttons layout
    QVBoxLayout* buttonsLayout = new QVBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignCenter);

    _resetScoresButton = new ButtonForMenu("D:/Qt_practice/doodlejump_sprites/sprites/menu@2x.png", "D:/Qt_practice/doodlejump_sprites/sprites/menu-on@2x.png", [](){}, this);
    _scoreMarkersButton = new ButtonForMenu("D:/Qt_practice/doodlejump_sprites/sprites/menu@2x.png", "D:/Qt_practice/doodlejump_sprites/sprites/menu-on@2x.png", [](){}, this);
    _selectBackgroundButton = new ButtonForMenu("D:/Qt_practice/doodlejump_sprites/sprites/menu@2x.png", "D:/Qt_practice/doodlejump_sprites/sprites/menu-on@2x.png", [](){}, this);
    _selectSpriteButton = new ButtonForMenu("D:/Qt_practice/doodlejump_sprites/sprites/menu@2x.png", "D:/Qt_practice/doodlejump_sprites/sprites/menu-on@2x.png", [](){}, this);
    _backButton = new ButtonForMenu("D:/Qt_practice/doodlejump_sprites/sprites/menu@2x.png", "D:/Qt_practice/doodlejump_sprites/sprites/menu-on@2x.png", [this](){ emit returnToMenuRequested(); }, this);

    const int spacing = qMax(15, static_cast<int>(height() * 0.02));

    buttonsLayout->addWidget(_resetScoresButton);
    buttonsLayout->addSpacing(spacing);
    buttonsLayout->addWidget(_scoreMarkersButton);
    buttonsLayout->addSpacing(spacing);
    buttonsLayout->addWidget(_selectBackgroundButton);
    buttonsLayout->addSpacing(spacing);
    buttonsLayout->addWidget(_selectSpriteButton);
    buttonsLayout->addWidget(_backButton);

    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}