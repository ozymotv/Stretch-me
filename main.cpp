#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Ensure only one instance
    QApplication::setQuitOnLastWindowClosed(false);
    
    MainWindow window;
    return app.exec();
}
