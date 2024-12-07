#include "mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    
    m_config = new Config();
    m_resolutionManager = new ResolutionManager(m_config, this);
    
    createTrayIcon();
    setupResolutionManager();
    
    // Start minimized
    hide();
    m_resolutionManager->startMonitoring();
}

MainWindow::~MainWindow() {
    m_resolutionManager->stopMonitoring();
}

void MainWindow::createTrayIcon() {
    QMenu* trayMenu = new QMenu(this);
    
    QAction* quitAction = new QAction("Quit", this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    
    trayMenu->addAction(quitAction);
    
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setContextMenu(trayMenu);
    m_trayIcon->setIcon(QIcon(":/icon.png")); // You'd need to add an app icon
    m_trayIcon->show();
}

void MainWindow::setupResolutionManager() {
    // Optional: Add configuration methods here
}
