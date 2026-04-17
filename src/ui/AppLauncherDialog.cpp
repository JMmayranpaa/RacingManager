//
// Created by juham on 17/04/2026.
//

#include "AppLauncherDialog.h"
#include <QDialogButtonBox>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFileDialog>
#include <QDialogButtonBox>

AppLauncherDialog::AppLauncherDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Applications");
    resize(800, 800);

    auto* mainLayout = new QVBoxLayout(this);

    auto* listGroup  = new QGroupBox("Applications", this);
    auto* listLayout = new QVBoxLayout(listGroup);

    appList = new QListWidget(listGroup);
    auto* removeBtn = new QPushButton("Remove Selected", listGroup);
    connect(removeBtn, &QPushButton::clicked,
            this, &AppLauncherDialog::removeSelected);

    listLayout->addWidget(appList);
    listLayout->addWidget(removeBtn);

    auto* addGroup  = new QGroupBox("Add Application", this);
    auto* addLayout = new QVBoxLayout(addGroup);

    nameEdit = new QLineEdit(addGroup);
    nameEdit->setPlaceholderText("Name (ie. iRacing UI)");

    auto* pathRow = new QHBoxLayout();
    pathEdit = new QLineEdit(addGroup);
    pathEdit->setPlaceholderText("Path to .exe file");
    auto* browseBtn = new QPushButton("Search...", addGroup);
    connect(browseBtn, &QPushButton::clicked,
            this, &AppLauncherDialog::browsePath);
    pathRow->addWidget(pathEdit);
    pathRow->addWidget(browseBtn);

    argsEdit = new QLineEdit(addGroup);
    argsEdit->setPlaceholderText("Arguments (optional)");

    auto* addBtn = new QPushButton("Add", addGroup);
    connect(addBtn, &QPushButton::clicked,
            this, &AppLauncherDialog::addApp);

    addLayout->addWidget(new QLabel("Name:"));
    addLayout->addWidget(nameEdit);
    addLayout->addWidget(new QLabel("Path:"));
    addLayout->addLayout(pathRow);
    addLayout->addWidget(new QLabel("Arguments:"));
    addLayout->addWidget(argsEdit);
    addLayout->addWidget(addBtn);

    auto* buttons = new QDialogButtonBox(
        QDialogButtonBox::Save | QDialogButtonBox::Cancel,
        this);
    connect(buttons, &QDialogButtonBox::accepted,
            this, &AppLauncherDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected,
            this, &AppLauncherDialog::reject);

    mainLayout->addWidget(listGroup);
    mainLayout->addWidget(addGroup);
    mainLayout->addWidget(buttons);

    loadApps();
}

void AppLauncherDialog::loadApps() {
    apps = launcher.loadConfig();
    refreshList();
}

void AppLauncherDialog::refreshList() {
    appList->clear();
    for (const auto& a : apps)
        appList->addItem(a.name + "  —  " + a.path);
}

void AppLauncherDialog::addApp() {
    if (nameEdit->text().isEmpty() || pathEdit->text().isEmpty())
        return;

    AppLauncher::ConfiguredApp app;
    app.name      = nameEdit->text();
    app.path      = pathEdit->text();
    app.arguments = argsEdit->text();
    apps.append(app);

    nameEdit->clear();
    pathEdit->clear();
    argsEdit->clear();
    refreshList();
}

void AppLauncherDialog::removeSelected() {
    int row = appList->currentRow();
    if (row >= 0 && row < apps.size()) {
        apps.removeAt(row);
        refreshList();
    }
}

void AppLauncherDialog::browsePath() {
    QString path = QFileDialog::getOpenFileName(
        this, "Select Application", "",
        "Applications (*.exe);;All Applications(*.*)");
    if (!path.isEmpty())
        pathEdit->setText(path);
}

void AppLauncherDialog::accept() {
    launcher.saveConfig(apps);
    QDialog::accept();
}