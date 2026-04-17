//
// Created by juham on 17/04/2026.
//

#ifndef RACINGMANAGER_DELTAOVERLAY_H
#define RACINGMANAGER_DELTAOVERLAY_H
#include <QWidget>
#include "../iracing/IRacingReader.h"


class QLabel;
class QTimer;
class IracingReader;

class DeltaOverlay : public QWidget {
    Q_OBJECT

public:
    explicit DeltaOverlay(QWidget* parent = nullptr);
    ~DeltaOverlay() override;

private:
    void poll();
private:
    void updateUI(const TelemetryData& data);

    QLabel* labelDelta;

    QTimer*         timer;
    IRacingReader*  reader;

    QPoint dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

};



#endif //RACINGMANAGER_DELTAOVERLAY_H
