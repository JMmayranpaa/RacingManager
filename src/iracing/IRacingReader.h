//
// Created by juham on 11/04/2026.
//

#ifndef RACINGMANAGER_IRACINGREADER_H
#define RACINGMANAGER_IRACINGREADER_H
#pragma once
#include <windows.h>
#include "irsdk_defines.h"
#include "TelemetryData.h"



class IRacingReader {
public:
    IRacingReader();
    ~IRacingReader();

    bool tryConnect();
    void disconnect();
    bool isConnected() const { return sharedMem != nullptr; }

    TelemetryData read();

private:
    HANDLE      hMapFile  = nullptr;
    const char* sharedMem = nullptr;

    const irsdk_varHeader* findVar(const char* name) const;
    float getFloat(const char* name) const;
    int   getInt(const char* name)   const;
};



#endif //RACINGMANAGER_IRACINGREADER_H
