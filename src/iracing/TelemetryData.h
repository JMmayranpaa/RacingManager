//
// Created by juham on 11/04/2026.
//

#ifndef RACINGMANAGER_TELEMETRYDATA_H
#define RACINGMANAGER_TELEMETRYDATA_H



struct TelemetryData {
    // Speed & Steering
    float speedKmh              = 0.f;
    float throttle              = 0.f; // 0-1
    float brake                 = 0.f; // 0-1 // Perhaps integer
    int gear                  = 0; // Perhaps integer

    // Laptimes
    float lastLapTime           = 0.f;
    float bestLapTime           = 0.f;
    float currentDelta          = 0.f; // + = slower that best lap time
    float lapDistPct            = 0.f; // 0-1

    // Fuel
    float fuelLevel             = 0.f; // In liters
    float fuelPerLap            = 0.f; // about

    // tires
    float tyreTempL[4] = {};
    float tyreTempM[4] = {};
    float tyreTempR[4] = {};

    // Race
    int position                = 0;
    int totalCars               = 0;
    float sessionTimeRemaining  = 0.f;

    bool isConnected            = false;

};



#endif //RACINGMANAGER_TELEMETRYDATA_H
