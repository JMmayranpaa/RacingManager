//
// Created by juham on 11/04/2026.
//

#ifndef RACINGMANAGER_OVERLAYWINDOW_H
#define RACINGMANAGER_OVERLAYWINDOW_H
#pragma once
#include <QWidget>
#include "../iracing/IRacingReader.h"


class QLabel;
class QTimer;
class IRacingReader;

class OverlayWindow : public QWidget {
    Q_OBJECT

public:
    explicit OverlayWindow( QWidget* parent = nullptr );
    ~OverlayWindow() override;

private slots:
    void poll();

private:
    void updateUI(const TelemetryData& data);

    //Labels
    QLabel* labelSpeed;
    QLabel* labelGear;
    QLabel* labelFuel;
    QLabel* labelDelta;
    QLabel* labelPosition;

    QTimer*         timer;
    IRacingReader*  reader;

    QPoint dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

};





#endif //RACINGMANAGER_OVERLAYWINDOW_H
