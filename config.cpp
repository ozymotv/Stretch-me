#include "config.h"
#include <QFile>
#include <QTextStream>

Config::Config(const QString& filename) {
    settings = new QSettings(filename, QSettings::IniFormat);
    
    if (!QFile::exists(filename)) {
        createDefaultConfig();
    }
}

void Config::createDefaultConfig() {
    settings->beginGroup("Profiles");
    settings->setValue("# Example", "1280x720");
    settings->setValue("# Example.exe", "1600x900");
    settings->endGroup();
    settings->sync();
}

QString Config::getResolution(const QString& title, const QString& executable) {
    settings->beginGroup("Profiles");
    
    // Check by title first
    QString titleRes = settings->value(title).toString();
    if (!titleRes.isEmpty()) {
        settings->endGroup();
        return titleRes;
    }
    
    // Then check by executable
    QString exeRes = settings->value(executable).toString();
    settings->endGroup();
    
    return exeRes;
}

void Config::setResolution(const QString& key, const QString& resolution) {
    settings->beginGroup("Profiles");
    settings->setValue(key, resolution);
    settings->endGroup();
    settings->sync();
}

void Config::save() {
    settings->sync();
}
