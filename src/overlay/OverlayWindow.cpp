//
// Created by juham on 11/04/2026.
//

#include "OverlayWindow.h"
#include "../iracing/IRacingReader.h"
#include <QLabel>
#include <QTimer>
#include <QHBoxLayout>
#include <QScreen>
#include <QApplication>
#include <QMouseEvent>
#include <windows.h>

OverlayWindow::OverlayWindow(QWidget* parent)
    : QWidget(parent,
              Qt::FramelessWindowHint |
              Qt::WindowStaysOnTopHint |
              Qt::Tool)
{
    setAttribute(Qt::WA_TranslucentBackground);

    // Tummapohjainen overlay-tyyli
    setStyleSheet(R"(
        QWidget {
            background-color: rgba(0, 0, 0, 180);
            border-radius: 8px;
        }
        QLabel {
            color: white;
            font-family: 'Consolas';
            font-size: 14px;
            padding: 2px 6px;
        }
    )");

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(4);

    labelPosition = new QLabel("POS: --",   this);
    labelSpeed    = new QLabel("SPD: --",   this);
    labelGear     = new QLabel("GEAR: --",  this);
    labelFuel     = new QLabel("FUEL: --",  this);
    labelDelta    = new QLabel("DELTA: --", this);

    // Isompi fontti nopeudelle ja vaihteelle
    labelSpeed->setStyleSheet("font-size: 22px; font-weight: bold;");
    labelGear->setStyleSheet("font-size: 22px; font-weight: bold;");

    layout->addWidget(labelPosition);
    layout->addWidget(labelSpeed);
    layout->addWidget(labelGear);
    layout->addWidget(labelFuel);
    layout->addWidget(labelDelta);

    setLayout(layout);
    resize(200, 220);

    // Sijoita oikeaan yläkulmaan
    QRect screen = QApplication::primaryScreen()->geometry();
    move(screen.width() - width() - 20, 20);

    // Ikkuna aina päällimmäiseksi
    SetWindowPos((HWND)winId(), HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE);

    reader = new IRacingReader();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &OverlayWindow::poll);
    timer->start(16); // ~60hz
}

OverlayWindow::~OverlayWindow() {
    delete reader;
}

void OverlayWindow::poll() {
    if (!reader->isConnected()) {
        reader->tryConnect();
        return;
    }
    updateUI(reader->read());
}

void OverlayWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }
}

void OverlayWindow::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton)
        move(event->globalPosition().toPoint() - dragPosition);
}

void OverlayWindow::updateUI(const TelemetryData& data) {
    if (!data.isConnected) return;

    labelPosition->setText(QString("POS: %1").arg(data.position));
    labelSpeed->setText(QString("SPEED: %1 km/h").arg((int)data.speedKmh));
    labelGear->setText(QString("GEAR: %1").arg(data.gear));
    labelFuel->setText(QString("FUEL: %1 L").arg(data.fuelLevel, 0, 'f', 1));

    // Delta värikoodattu
    QString deltaStr = QString("DELTA: %1%2")
        .arg(data.currentDelta >= 0 ? "+" : "")
        .arg(data.currentDelta, 0, 'f', 3);

    labelDelta->setText(deltaStr);
    labelDelta->setStyleSheet(
        data.currentDelta > 0
            ? "color: red;   font-size: 14px;"
            : "color: #00ff00; font-size: 14px;"
    );
}