#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "config.h"
#include "resolutionmanager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Config* m_config;
    ResolutionManager* m_resolutionManager;
    QSystemTrayIcon* m_trayIcon;

    void createTrayIcon();
    void setupResolutionManager();
};

#endif // MAINWINDOW_H
