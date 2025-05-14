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
//#include"ScoresState.h"
//#include"OptionsState.h"
//#include"JsonScoreManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QApplication*);
    void run();
private slots:
    void playButtonPressed();
    //void highScoresButtonPressed();
    //void optionsButtonPressed();
    void exitButtonPressed();
    void returnToMenu();
    //void saveResult(const QString& name, int score);
    void setupActingState();
    void setupMenuState();
    //void setupOptionsState();
    //void clearHighScores();
protected:
    void closeEvent(QCloseEvent*) override;
private:
    QScreen* _userScreen;
    QApplication* _app;
    MenuState* _menuState;
    ActingState* _actingState;
    //OptionsState* _optionsState;
    //JsonScoreManager _scoreManager;
    GameState _currentState;
    bool _isRunning = true;
};

#endif //MAIN_WINDOW