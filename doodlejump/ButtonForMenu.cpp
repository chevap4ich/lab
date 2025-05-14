#include "ButtonForMenu.h"
#include <QIcon>
#include <QPixmap>
#include <QPixmap>

ButtonForMenu::ButtonForMenu(const QString& imagePath, const QString& imageBGPath, const std::function<void()>& slot, QWidget* parent) 
                    : QPushButton(parent), _clickAction(slot)
{
    QPixmap buttonImage(imagePath); 
    QPixmap buttonImageBG(imageBGPath);
    if (buttonImage.isNull() || buttonImageBG.isNull()) {
        qDebug() << "Error: Failed to load button image(s).";
        return;
    }
    setFixedSize(parent->height() * 0.075 * 2.78 , parent->height() * 0.075);
    buttonImage = buttonImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setIcon(QIcon(buttonImage));
    setIconSize(this->size());
    setStyleSheet( "QPushButton { border: none; background: transparent; }" );
    connect(this, &QPushButton::pressed, [=]() { this->setIcon(QIcon(buttonImageBG)); });
    connect(this, &QPushButton::released, [=]() { this->setIcon(QIcon(buttonImage)); });
    
    connect(this, &ButtonForMenu::clicked, this, &ButtonForMenu::handleButtonClick);
}

void ButtonForMenu::handleButtonClick()
{
    if (_clickAction) {
        _clickAction();
    }
    emit buttonPressed();
}