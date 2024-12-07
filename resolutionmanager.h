#ifndef RESOLUTIONMANAGER_H
#define RESOLUTIONMANAGER_H

#include <QObject>
#include <Windows.h>
#include "config.h"

class ResolutionManager : public QObject {
    Q_OBJECT

public:
    explicit ResolutionManager(Config* config, QObject *parent = nullptr);
    void startMonitoring();
    void stopMonitoring();

private:
    Config* m_config;
    bool m_isMonitoring;
    int m_pollInterval;

    struct WindowInfo {
        QString title;
        QString executable;
        HWND hwnd;
    };

    WindowInfo getCurrentWindowInfo();
    void changeResolution(const QString& resolution);
    void resetResolution();
};

#endif // RESOLUTIONMANAGER_H
