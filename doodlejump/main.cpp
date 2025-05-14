#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include "MainWindow.h"
#include "ActingState.h"
#include "platform.h"
#include "menuState.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow wnd(&app);
    wnd.show();
    wnd.run();
    app.exit();
}