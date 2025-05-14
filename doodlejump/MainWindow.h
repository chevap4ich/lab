#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include<QApplication>
#include<QMainWindow>
#include<QCloseEvent>
#include<QScreen>
#include<QRect>
#include<QIcon>
#include<QDateTime>
#include<vector>
#include"config.h"
#include"MenuState.h"
#include"ActingState.h"
#include"OptionsState.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QApplication*);
    void run();
private slots:
    void playButtonPressed();
    void exitButtonPressed();
    void returnToMenu();
    void setupActingState();
    void setupMenuState();
    void setupOptionsState();
    void optionsButtonPressed();
    void highScoresButtonPressed();
protected:
    void closeEvent(QCloseEvent*) override;
private:
    QScreen* _userScreen;
    QApplication* _app;
    MenuState* _menuState;
    ActingState* _actingState;
    OptionsState* _optionsState;
    GameState _currentState;
    bool _isRunning = true;
};

#endif //MAIN_WINDOW