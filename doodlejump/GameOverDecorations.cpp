#include "GameOverDecorations.h"
#include <QPainter>

GameOverDecorations::GameOverDecorations(QWidget* parent) : QWidget(parent) {
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(parent->width(), parent->height());

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* youLose = new QLabel(this);
    QPixmap pixmapYouLoseLabel("D:\\Qt_practice\\doodlejump_sprites\\sprites\\game_over.png");
    pixmapYouLoseLabel = pixmapYouLoseLabel.scaled(width() * 0.7, width() * 0.7 * 132 / 380, Qt::IgnoreAspectRatio);
    youLose->setPixmap(pixmapYouLoseLabel);
    youLose->setFixedSize(pixmapYouLoseLabel.size());
    youLose->setAlignment(Qt::AlignCenter);

    QWidget *nameContainer = new QWidget(this);
    QHBoxLayout *nameLayout = new QHBoxLayout(nameContainer);
    nameLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *namePrefix = new QLabel("Name:", this);
    namePrefix->setStyleSheet("color: black; font: 28px;");
    namePrefix->setFont(QFont("Segoe Print"));
    
    _nameEdit = new QLineEdit(this);
    _nameEdit->setFixedWidth(width() * 0.35);
    _nameEdit->setPlaceholderText("enter here!");
    _nameEdit->setText("player");
    _nameEdit->setAlignment(Qt::AlignCenter);
    _nameEdit->setFont(QFont("Segoe Print"));
    _nameEdit->setFrame(false);
    _nameEdit->setStyleSheet(
        "QLineEdit {"
        "   background: transparent;"
        "   border: none;"
        "   color: black;"
        "   font-size: 28px;"
        "   padding: 0px;"
        "}"
    );
    
    nameLayout->addWidget(namePrefix, 0, Qt::AlignRight);
    nameLayout->addWidget(_nameEdit, 0, Qt::AlignLeft);

    _scoreLabel = new QLabel(this);
    _scoreLabel->setStyleSheet("color: black; font: 28px;");
    _scoreLabel->setFont(QFont("Segoe Print"));
    _scoreLabel->setAlignment(Qt::AlignCenter);

    QLabel* bottomLabel = new QLabel(this);
    QPixmap pixmapBottomLabel("D:\\Qt_practice\\doodlejump_sprites\\sprites\\bottom.png");
    pixmapBottomLabel = pixmapBottomLabel.scaled(width(), width() * 0.338, Qt::IgnoreAspectRatio);
    bottomLabel->setPixmap(pixmapBottomLabel);
    bottomLabel->setFixedSize(pixmapBottomLabel.size());
    bottomLabel->setAlignment(Qt::AlignBottom | Qt::AlignCenter);

    _playAgainButton = new ButtonForMenu("D:\\Qt_practice\\doodlejump_sprites\\sprites\\play-again-on@2x.png",
        "D:\\Qt_practice\\doodlejump_sprites\\sprites\\play-again-on@2x.png",
         [this](){ emit playAgainRequested(); }, this);

    QHBoxLayout* playAgainButtonLayout = new QHBoxLayout();
    playAgainButtonLayout->addWidget(_playAgainButton);
    playAgainButtonLayout->setContentsMargins(0, 0, width() * 0.35, 0);
    
    _menuButton = new ButtonForMenu("D:\\Qt_practice\\doodlejump_sprites\\sprites\\menu@2x.png",
        "D:\\Qt_practice\\doodlejump_sprites\\sprites\\menu-on@2x.png",
         [this](){ emit menuRequested(); }, this);

    QHBoxLayout* menuButtonLayout = new QHBoxLayout();
    menuButtonLayout->addWidget(_menuButton);
    menuButtonLayout->setContentsMargins(width() * 0.25, 0, 0, 0);

    mainLayout->addStretch(1);
    mainLayout->addWidget(youLose, 0, Qt::AlignCenter);
    mainLayout->addSpacing(height() * 0.05);
    mainLayout->addWidget(_scoreLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(nameContainer, 0, Qt::AlignCenter);
    mainLayout->addSpacing(height() * 0.05);
    //mainLayout->addLayout(saveButtonLayout);
    mainLayout->addLayout(playAgainButtonLayout);
    mainLayout->addLayout(menuButtonLayout);
    mainLayout->addWidget(bottomLabel, 0, Qt::AlignBottom | Qt::AlignCenter);

    setLayout(mainLayout);
}


void GameOverDecorations::animateShow() 
{
    show();
    raise();
    _animation = new QPropertyAnimation(this, "pos");
    _animation->setDuration(800);
    _animation->setStartValue(QPoint(0, parentWidget()->height()));
    _animation->setEndValue(QPoint(0, 0));
    _animation->setEasingCurve(QEasingCurve::OutQuad);
    _animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void GameOverDecorations::setScore(int score) {
    _scoreLabel->setText("Score: " + QString::number(score));
}