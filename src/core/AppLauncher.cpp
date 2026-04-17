//
// Created by juham on 17/04/2026.
//

#include "AppLauncher.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>
#include <QProcess>

AppLauncher::AppLauncher() {}

// Config filepath C:/Users/[USERNAME]/AppData/Local/RacingManager
QString AppLauncher::configFilePath() const {
    QString dir = QStandardPaths::writableLocation(
        QStandardPaths::AppConfigLocation);
    QDir().mkpath(dir);
    return dir + "/apps.json"; // Could rename something like LaunchApplications.json ??
}

QList<AppLauncher::ConfiguredApp> AppLauncher::loadConfig() const {
    QList<ConfiguredApp> result;

    QFile f(configFilePath());
    if (!f.open(QIODevice::ReadOnly)) return result;

    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    if (!doc.isArray()) return result;

    for (const auto& v : doc.array()) {
        QJsonObject o = v.toObject();
        ConfiguredApp app;
        app.name      = o["name"].toString();
        app.path      = o["path"].toString();
        app.arguments = o["arguments"].toString();
        result.append(app);
    }
    return result;
}

void AppLauncher::saveConfig(const QList<ConfiguredApp>& apps) const {
    QJsonArray arr;
    for (const auto& app : apps) {
        QJsonObject o;
        o["name"]      = app.name;
        o["path"]      = app.path;
        o["arguments"] = app.arguments;
        arr.append(o);
    }

    QFile f(configFilePath());
    if (f.open(QIODevice::WriteOnly)) {
        f.write(QJsonDocument(arr).toJson());
    }
}

bool AppLauncher::launchApp(const ConfiguredApp& app) {
    if (app.path.isEmpty()) return false;

    QStringList args;
    if (!app.arguments.isEmpty())
        args = app.arguments.split(" ", Qt::SkipEmptyParts);

    return QProcess::startDetached(app.path, args);
}

void AppLauncher::launchAllFromConfig() {
    for (const auto& app : loadConfig())
        launchApp(app);
}