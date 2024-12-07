#include "resolutionmanager.h"
#include <QTimer>
#include <QThread>
#include <QFileInfo>
#include <psapi.h>

ResolutionManager::ResolutionManager(Config* config, QObject *parent)
    : QObject(parent), m_config(config), m_isMonitoring(false) {
    
    // Determine polling interval based on processor count
    int processorCount = QThread::idealThreadCount();
    if (processorCount <= 4) m_pollInterval = 1000;
    else if (processorCount <= 7) m_pollInterval = 100;
    else m_pollInterval = 1;
}

ResolutionManager::WindowInfo ResolutionManager::getCurrentWindowInfo() {
    WindowInfo info;
    HWND hwnd = GetForegroundWindow();
    
    if (hwnd) {
        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);
        
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
        if (hProcess) {
            // Get window title
            int length = GetWindowTextLength(hwnd) + 1;
            std::vector<wchar_t> title(length);
            GetWindowText(hwnd, title.data(), length);
            info.title = QString::fromWCharArray(title.data());
            
            // Get executable name
            std::vector<wchar_t> exePath(MAX_PATH);
            if (GetModuleFileNameEx(hProcess, NULL, exePath.data(), MAX_PATH)) {
                QFileInfo fileInfo(QString::fromWCharArray(exePath.data()));
                info.executable = fileInfo.fileName();
            }
            
            info.hwnd = hwnd;
            
            CloseHandle(hProcess);
        }
    }
    
    return info;
}

void ResolutionManager::changeResolution(const QString& resolution) {
    QStringList parts = resolution.split('x');
    if (parts.size() != 2) return;
    
    DEVMODE dm = {0};
    dm.dmSize = sizeof(DEVMODE);
    dm.dmPelsWidth = parts[0].toInt();
    dm.dmPelsHeight = parts[1].toInt();
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
    
    ChangeDisplaySettings(&dm, 0);
}

void ResolutionManager::resetResolution() {
    ChangeDisplaySettings(NULL, 0);
}

void ResolutionManager::startMonitoring() {
    m_isMonitoring = true;
    QTimer* timer = new QTimer(this);
    
    connect(timer, &QTimer::timeout, this, [this]() {
        if (!m_isMonitoring) return;
        
        WindowInfo info = getCurrentWindowInfo();
        QString resolution = m_config->getResolution(info.title, info.executable);
        
        if (!resolution.isEmpty()) {
            changeResolution(resolution);
        } else {
            resetResolution();
        }
    });
    
    timer->start(m_pollInterval);
}

void ResolutionManager::stopMonitoring() {
    m_isMonitoring = false;
}
