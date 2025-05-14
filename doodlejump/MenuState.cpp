#include "MenuState.h"

MenuState::MenuState(QWidget* parent) : QWidget(parent) {
    
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(parent->width(), parent->height());

    createSprites();

    QLabel* backgroundLabel = new QLabel(this);
    QPixmap pixmapBG("D:/Qt_practice/doodlejump_sprites/sprites/bck.png");
    if (pixmapBG.isNull()) {
        qDebug() << "Error: Failed to load image: ";
        // Обработайте ошибку: возможно, загрузите изображение по умолчанию или выйдите из функции
        return;
    }
    pixmapBG = pixmapBG.scaled(width(), width() * 1.6, Qt::KeepAspectRatio);
    backgroundLabel->setGeometry(geometry());
    backgroundLabel->setPixmap(pixmapBG);
    backgroundLabel->lower();
    
    QVBoxLayout* menuLayout = new QVBoxLayout();
    menuLayout->setContentsMargins(0, width() * 0.03, 0, 0);
    menuLayout->setSpacing(0);

    QHBoxLayout* menuLayoutH = new QHBoxLayout();
    menuLayoutH->setContentsMargins(0, 0, 0, 0);
    menuLayoutH->setSpacing(0);

    QLabel* gameNameLabel = new QLabel(this);
    //gameNameLabel->setStyleSheet("background-color: green;");
    QPixmap pixmapGameNameLabel("D:/Qt_practice/doodlejump_sprites/sprites/doodle-jump@2x.png");
    pixmapGameNameLabel = pixmapGameNameLabel.scaled(width() * 1.2, width() * 1.2 * (404 / 92), Qt::KeepAspectRatio);
    gameNameLabel->setFixedSize(width() * 0.7, height() * 0.25);
    gameNameLabel->setPixmap(pixmapGameNameLabel);
    gameNameLabel->setAlignment(Qt::AlignCenter);
    menuLayoutH->addWidget(gameNameLabel);

    QLabel* ufoLabel = new QLabel(this);
    //ufoLabel->setStyleSheet("background-color: yellow; border: 2px solid black;");
    QPixmap pixmapUfoLabel("D:/Qt_practice/doodlejump_sprites/sprites/ufo.png");
    pixmapUfoLabel = pixmapUfoLabel.scaled(width() * 0.3, height() * 0.25, Qt::KeepAspectRatio);
    ufoLabel->setFixedSize(width() * 0.33, height() * 0.25);
    ufoLabel->setPixmap(pixmapUfoLabel);
    menuLayoutH->addWidget(ufoLabel);

    QWidget* menuLayoutHWidget = new QWidget();
    menuLayoutHWidget->setLayout(menuLayoutH);

    QLabel* bottomLabel = new QLabel(this);
    //bottomLabel->setStyleSheet("background-color: blue; ");
    QPixmap pixmapBottomLabel("D:/Qt_practice/doodlejump_sprites/sprites/bottom.png"); 
    pixmapBottomLabel = pixmapBottomLabel.scaled(width(), width() * 0.338, Qt::IgnoreAspectRatio);
    bottomLabel->setFixedSize(width(), width() * 0.338);
    bottomLabel->setPixmap(pixmapBottomLabel);
    bottomLabel->setAlignment(Qt::AlignBottom | Qt::AlignCenter);

    QVBoxLayout* buttonsLayout = new QVBoxLayout(this);
    _playButton = new ButtonForMenu("D:/Qt_practice/doodlejump_sprites/sprites/play@2x.png",
        "D:/Qt_practice/doodlejump_sprites/sprites/play-on@2x.png",
         [this](){ emit playRequested(); }, this);
    /*_highScoresButton = new ButtonForMenu("D:\\Qt practice\\doodlejump_sprites\\sprites\\scores-on@2x.png",
        "D:\\Qt practice\\doodlejump_sprites\\sprites\\scores-on@2x.png",
         [this](){ emit highScoresRequested(); }, this);
    _optionsButton = new ButtonForMenu("D:\\Qt practice\\doodlejump_sprites\\sprites\\options@2x.png",
        "D:\\Qt practice\\doodlejump_sprites\\sprites\\options-on@2x.png",
         [this](){ emit optionsRequested(); }, this);*/
    _exitButton = new ButtonForMenu("D:/Qt_practice/doodlejump_sprites/sprites/cancel@2x.png",
        "D:/Qt_practice/doodlejump_sprites/sprites/cancel-on@2x.png",
         [this](){ emit exitRequested(); }, this);

    const int spacing = qMax(15, static_cast<int>(height() * 0.02));
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
         
    buttonsLayout->addWidget(_playButton);
    buttonsLayout->addSpacing(spacing);
    //buttonsLayout->addWidget(_highScoresButton);
    //buttonsLayout->addSpacing(spacing);
    //buttonsLayout->addWidget(_optionsButton);
    //buttonsLayout->addSpacing(spacing);
    buttonsLayout->addWidget(_exitButton);

    buttonsLayout->setAlignment(Qt::AlignCenter);

    QWidget *buttonContainer = new QWidget();
    buttonContainer->setFixedSize(width(), height() * 0.72 - bottomLabel->height());
    buttonContainer->setLayout(buttonsLayout);
    //buttonContainer->setStyleSheet("background-color: red; border: 2px solid black;");

    menuLayout->addWidget(menuLayoutHWidget);
    menuLayout->addWidget(buttonContainer);
    menuLayout->addWidget(bottomLabel);

    setLayout(menuLayout);
}

void MenuState::update(float deltaTime) {
    for (auto& sprite : _sprites) {
        if (sprite) 
            sprite->updatePosition(deltaTime);
    }
}

void MenuState::createSprites() {
    for (int i = 0; i < 11; ++i) {
        auto sprite = std::make_unique<MoveSprite>(this);
        QString imagePath;
        if(sprite->_speed > 0){
            imagePath = QString("D:/Qt_practice/doodlejump_sprites/sprites/space-right@2x.png")/*.arg(i+1)*/;
        } else {
            imagePath = QString("D:/Qt_practice/doodlejump_sprites/sprites/space-left@2x.png")/*.arg(i+1)*/;
        }
        sprite->setImage(imagePath);
        //sprite->setAttribute(Qt::WA_TranslucentBackground);
        sprite->lower();
        _sprites.push_back(std::move(sprite));  
    }
}