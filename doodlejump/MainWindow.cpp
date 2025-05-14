#include "MainWindow.h"
#include "MoveSprite.h"
#include "config.h"
//#include "HighScoresWindow.h"

MainWindow::MainWindow(QApplication* app): QMainWindow(), _app(app){

    setFixedSize(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint, true);
    setWindowTitle("Doodle Jump");
    app->setWindowIcon(QIcon("D:\\Qt_practice\\doodlejump_sprites\\sprites\\ach-ufo@2x.png"));
    
    //????
    _userScreen = QApplication::primaryScreen();
    QRect userScreenRect = _userScreen->availableGeometry();
    int x = (userScreenRect.width() - SCREEN_SIZE_X) / 2;
    int y = (userScreenRect.height() - SCREEN_SIZE_Y) / 2;
    this->move(x, y);

    setupMenuState();
}

void MainWindow::run(){
    uint64_t time = QDateTime::currentMSecsSinceEpoch();
    while(_isRunning){
        _app->processEvents();
       
        uint64_t newTime = QDateTime::currentMSecsSinceEpoch();
        float deltaTime = float(newTime - time)/SIMULATION_SPEED;

        switch (_currentState) {
        case GameState::Menu:
            _menuState->update(deltaTime);
            break;
        case GameState::Acting:
            _actingState->update(deltaTime);
            break;  
        case GameState::Options:
            
            break;    
        }
        
        this->repaint();
        time = newTime;
    }
}

void MainWindow::playButtonPressed() {
    setupActingState();
}


void MainWindow::setupActingState() {
    _actingState = new ActingState(this);
    connect(_actingState, &ActingState::restartRequested, this, &MainWindow::setupActingState);
    connect(_actingState, &ActingState::returnToMenuRequested, this, &MainWindow::returnToMenu);
    this->setCentralWidget(_actingState);
    _currentState = GameState::Acting;
}

void MainWindow::setupMenuState(){
    _menuState = new MenuState(this);
    connect(_menuState, &MenuState::playRequested, this, &MainWindow::playButtonPressed);
    connect(_menuState, &MenuState::highScoresRequested, this, &MainWindow::highScoresButtonPressed);
    connect(_menuState, &MenuState::optionsRequested, this, &MainWindow::optionsButtonPressed);
    connect(_menuState, &MenuState::exitRequested, this, &MainWindow::exitButtonPressed);
    this->setCentralWidget(_menuState);
    _currentState = GameState::Menu;
}

void MainWindow::setupOptionsState() {
    _optionsState = new OptionsState(this);
    connect(_optionsState, &OptionsState::returnToMenuRequested, this, &MainWindow::returnToMenu);
    this->setCentralWidget(_optionsState);
    _currentState = GameState::Options;
}


void MainWindow::returnToMenu() {
    setupMenuState();
}


void MainWindow::exitButtonPressed() {
    close();
}

void MainWindow::highScoresButtonPressed() {
    /*HighScoresWindow highScoresDialog(this);
    highScoresDialog.exec();*/
}

void MainWindow::optionsButtonPressed() { 
    setupOptionsState();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    _isRunning = false;
    QMainWindow::closeEvent(event);
}
