//
// Created by juham on 17/04/2026.
//

#include "OverlayManager.h"
#include "../overlay/OverlayWindow.h"
#include "../overlay/DeltaOverlay.h"

OverlayManager::OverlayManager(QObject* parent)
    : QObject(parent) {}

OverlayManager::~OverlayManager() {
    delete deltaOverlay;
}

void OverlayManager::showOverlayWindow() {
    if (!overlayWindow) {
        overlayWindow = new OverlayWindow();
    }
    overlayWindow->show();
}

void OverlayManager::hideOverlayWindow() {
    if (overlayWindow) {
        overlayWindow->hide();
    }
}

void OverlayManager::showDeltaOverlay() {
    if (!deltaOverlay)
        deltaOverlay = new DeltaOverlay();
    deltaOverlay->show();
}

void OverlayManager::hideDeltaOverlay() {
    if (deltaOverlay)
        deltaOverlay->hide();
}