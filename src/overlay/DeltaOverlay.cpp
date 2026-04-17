//
// Created by juham on 17/04/2026.
//

#include "DeltaOverlay.h"
#include "../iracing/IRacingReader.h"
#include <QLabel>
#include <QTimer>
#include <QHBoxLayout>
#include <QScreen>
#include <QApplication>
#include <QMouseEvent>
#include <windows.h>

DeltaOverlay::DeltaOverlay(QWidget* parent)
    : QWidget(parent,
              Qt::FramelessWindowHint |
              Qt::WindowStaysOnTopHint |
              Qt::Tool)
{
    setAttribute(Qt::WA_TranslucentBackground);

    // Dark overlay style
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

    labelDelta    = new QLabel("DELTA: --", this);

    layout->addWidget(labelDelta);

    setLayout(layout);
    resize(200, 220);

    // Place right top corner
    QRect screen = QApplication::primaryScreen()->geometry();
    move(screen.width() - width() - 20, 20);

    // Overlay window allways on top
    SetWindowPos((HWND)winId(), HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE);

    reader = new IRacingReader();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DeltaOverlay::poll);
    timer->start(16); // ~60hz
}

DeltaOverlay::~DeltaOverlay() {
    delete reader;
}

void DeltaOverlay::poll() {
    if (!reader->isConnected()) {
        reader->tryConnect();
        return;
    }
    updateUI(reader->read());
}

void DeltaOverlay::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }
}

void DeltaOverlay::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton)
        move(event->globalPosition().toPoint() - dragPosition);
}

void DeltaOverlay::updateUI(const TelemetryData& data) {
    if (!data.isConnected) return;

    // Delta color coded
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
