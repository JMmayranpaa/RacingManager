//
// Created by juham on 17/04/2026.
//

#ifndef RACINGMANAGER_APPLAUNCHERDIALOG_H
#define RACINGMANAGER_APPLAUNCHERDIALOG_H



#pragma once
#include <QDialog>
#include "../core/AppLauncher.h"

class QListWidget;
class QLineEdit;

class AppLauncherDialog : public QDialog {
    Q_OBJECT

public:
    explicit AppLauncherDialog(QWidget* parent = nullptr);

private slots:
    void addApp();
    void removeSelected();
    void browsePath();
    void accept() override;

private:
    void loadApps();
    void refreshList();

    QListWidget* appList;
    QLineEdit*   nameEdit;
    QLineEdit*   pathEdit;
    QLineEdit*   argsEdit;

    AppLauncher                       launcher;
    QList<AppLauncher::ConfiguredApp> apps;
};

#endif //RACINGMANAGER_APPLAUNCHERDIALOG_H
