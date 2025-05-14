#ifndef BUTTON_FOR_MENU
#define BUTTON_FOR_MENU

#include <QPushButton>
#include <functional>

//переименовать в обычный буттон

class ButtonForMenu : public QPushButton
{
    Q_OBJECT
public:
    ButtonForMenu(const QString&, const QString&, const std::function<void()>&, QWidget* = nullptr);
signals:
    void buttonPressed();
private slots:
    void handleButtonClick();
private:    
    std::function<void()> _clickAction;
};

#endif // BUTTON_FOR_MENU