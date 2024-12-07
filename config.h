#ifndef CONFIG_H
#define CONFIG_H

#include <QMap>
#include <QString>
#include <QSettings>

class Config {
public:
    Config(const QString& filename = "Options.ini");
    
    QString getResolution(const QString& title, const QString& executable);
    void setResolution(const QString& key, const QString& resolution);
    void save();

private:
    QSettings* settings;
    void createDefaultConfig();
};

#endif // CONFIG_H
