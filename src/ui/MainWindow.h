//
// Created by juham on 17/04/2026.
//

#ifndef RACINGMANAGER_MAINWINDOW_H
#define RACINGMANAGER_MAINWINDOW_H

#pragma once
#include <QMainWindow>

#include "AppLauncherDialog.h"

class QCheckBox;
class OverlayManager;
class SettingsDialog;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onDeltaOverlayToggled(bool checked);
    void onOverlayWindowToggled(bool checked);
    void openAppLauncher();

private:
    void setupUi();
    void launchConfiguredApps();

    QCheckBox*      deltaOverlayCheck;
    QCheckBox*      overlayWindowCheck;
    OverlayManager* overlayManager;
    AppLauncherDialog* appLauncherDialog;
};

#endif //RACINGMANAGER_MAINWINDOW_H
