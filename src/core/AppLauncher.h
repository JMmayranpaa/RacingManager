//
// Created by juham on 17/04/2026.
//

#ifndef RACINGMANAGER_APPLAUNCHER_H
#define RACINGMANAGER_APPLAUNCHER_H



#pragma once
#include <QString>
#include <QList>

class AppLauncher {
public:
    struct ConfiguredApp {
        QString name;
        QString path;
        QString arguments;
    };

    AppLauncher();

    QList<ConfiguredApp> loadConfig() const;
    void saveConfig(const QList<ConfiguredApp>& apps) const;

    void launchAllFromConfig();
    bool launchApp(const ConfiguredApp& app);

private:
    QString configFilePath() const;
};



#endif //RACINGMANAGER_APPLAUNCHER_H
