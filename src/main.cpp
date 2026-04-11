#include <iostream>
#include <QCoreApplication>
#include <QTimer>
#include "iracing/IracingReader.h"

#include "iracing/IRacingReader.h"


int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    IRacingReader reader;
    QTimer timer;

    QObject::connect(&timer, &QTimer::timeout, [&]() {
       if (!reader.isConnected()) {
           reader.tryConnect();
           printf("Waiting for Iracing...\n");
           return;
       }
        TelemetryData d = reader.read();
        printf("Speed: %.1f km/h Fuel: %.2f l/min Gear: %d /6 Pos: %d\n", d.speedKmh, d.fuelLevel, d.gear, d.position);
    });

    timer.start(500);
    return app.exec();

}
