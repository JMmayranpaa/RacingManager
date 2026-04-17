//
// Created by juham on 17/04/2026.
//

#ifndef RACINGMANAGER_OVERLAYMANAGER_H
#define RACINGMANAGER_OVERLAYMANAGER_H

#pragma once
#include <QObject>

class OverlayWindow;
class DeltaOverlay;

class OverlayManager : public QObject {
    Q_OBJECT

public:
    explicit OverlayManager(QObject* parent = nullptr);
    ~OverlayManager() override;

    void showOverlayWindow();
    void hideOverlayWindow();

    void showDeltaOverlay();
    void hideDeltaOverlay();

private:
    OverlayWindow* overlayWindow= nullptr;
    DeltaOverlay* deltaOverlay = nullptr;
};

#endif //RACINGMANAGER_OVERLAYMANAGER_H
