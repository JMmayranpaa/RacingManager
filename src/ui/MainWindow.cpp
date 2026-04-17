//
// Created by juham on 17/04/2026.
//

#include "MainWindow.h"
#include "OverlayManager.h"
#include "../core/AppLauncher.h"
#include "AppLauncherDialog.h"
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Racing Manager");
    resize(800, 800);

    overlayManager = new OverlayManager(this);
    appLauncherDialog = new AppLauncherDialog(this);

    setupUi();
    launchConfiguredApps();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi() {
    auto* central = new QWidget(this);
    auto* layout  = new QVBoxLayout(central);

    // Overlays group
    auto* overlayGroup = new QGroupBox("Overlays", central);
    auto* overlayLayout = new QVBoxLayout(overlayGroup);

    deltaOverlayCheck = new QCheckBox("Delta Overlay", overlayGroup);
    connect(deltaOverlayCheck, &QCheckBox::toggled,
            this, &MainWindow::onDeltaOverlayToggled);

    overlayWindowCheck = new QCheckBox("Overlay Window", overlayGroup);
    connect(overlayWindowCheck, &QCheckBox::toggled,
        this, &MainWindow::onOverlayWindowToggled);

    overlayLayout->addWidget(deltaOverlayCheck);
    overlayLayout->addWidget(overlayWindowCheck);
    overlayLayout->addStretch();

    // Application launcher options
    auto* settingsBtn = new QPushButton("Application launcher...", central);
    connect(settingsBtn, &QPushButton::clicked,
            this, &MainWindow::openAppLauncher);

    layout->addWidget(overlayGroup);
    layout->addWidget(settingsBtn);
    layout->addStretch();

    setCentralWidget(central);
}

void MainWindow::onDeltaOverlayToggled(bool checked) {
    if (checked) overlayManager->showDeltaOverlay();
    else         overlayManager->hideDeltaOverlay();
}

void MainWindow::onOverlayWindowToggled(bool checked) {
    if (checked) overlayManager->showOverlayWindow();
    else         overlayManager->hideOverlayWindow();
}

void MainWindow::openAppLauncher() {
    appLauncherDialog->exec();
}

void MainWindow::launchConfiguredApps() {
    AppLauncher launcher;
    launcher.launchAllFromConfig();
}