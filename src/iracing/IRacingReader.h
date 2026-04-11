//
// Created by juham on 11/04/2026.
//

#ifndef RACINGMANAGER_IRACINGREADER_H
#define RACINGMANAGER_IRACINGREADER_H
#pragma once
#include "TelemetryData.h"
#include "windows.h"



class IRacingReader {
public:
    IRacingReader();
    ~IracingReader();

    bool tryConnect();
    bool disconnect();
    bool isConnected() const { return sharedMem != nullptr; };

    TelemetryData read();
private:
    HANDLE          hMapFile    = nullptr;
    const char* sharedMem       = nullptr;

    float getFloat(const char* name)    const;
    int getInt(const char* name)        const;
    double getDouble(const char* name)  const;


};



#endif //RACINGMANAGER_IRACINGREADER_H
