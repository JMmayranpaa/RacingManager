//
// Created by juham on 11/04/2026.
//

#include "IRacingReader.h"

#include <cstring>

IRacingReader::IRacingReader() {}

IRacingReader::~IRacingReader() {
    disconnect();
}

bool IRacingReader::tryConnect() {
    if (sharedMem) return true;

    hMapFile = OpenFileMappingA(FILE_MAP_READ, FALSE,
                                "Local\\IRSDKMemMapFileName");
    if (!hMapFile) return false;

    sharedMem = (const char*)MapViewOfFile(
        hMapFile, FILE_MAP_READ, 0, 0, 0);

    if (!sharedMem) {
        CloseHandle(hMapFile);
        hMapFile = nullptr;
        return false;
    }
    return true;
}

void IRacingReader::disconnect() {
    if (sharedMem) {
        UnmapViewOfFile(sharedMem);
        sharedMem = nullptr;
    }
    if (hMapFile) {
        CloseHandle(hMapFile);
        hMapFile = nullptr;
    }
}

const irsdk_varHeader* IRacingReader::findVar(const char* name) const {
    if (!sharedMem) return nullptr;
    auto* hdr  = (const irsdk_header*)sharedMem;
    auto* vars = (const irsdk_varHeader*)(sharedMem + hdr->varHeaderOffset);
    for (int i = 0; i < hdr->numVars; i++) {
        if (strcmp(vars[i].name, name) == 0)
            return &vars[i];
    }
    return nullptr;
}

float IRacingReader::getFloat(const char* name) const {
    auto* var = findVar(name);
    if (!var) return 0.f;
    auto* hdr = (const irsdk_header*)sharedMem;
    return *(float*)(sharedMem + hdr->varBuf[0].bufOffset + var->offset);
}

int IRacingReader::getInt(const char* name) const {
    auto* var = findVar(name);
    if (!var) return 0;
    auto* hdr = (const irsdk_header*)sharedMem;
    return *(int*)(sharedMem + hdr->varBuf[0].bufOffset + var->offset);
}

TelemetryData IRacingReader::read() {
    TelemetryData d;
    if (!sharedMem) return d;

    auto* hdr = (const irsdk_header*)sharedMem;
    if (!(hdr->status & irsdk_stConnected)) return d;

    d.isConnected         = true;
    d.speedKmh            = getFloat("Speed") * 3.6f;
    d.throttle            = getFloat("Throttle");
    d.brake               = getFloat("Brake");
    d.gear                = getInt("Gear");
    d.lastLapTime         = getFloat("LapLastLapTime");
    d.bestLapTime         = getFloat("LapBestLapTime");
    d.currentDelta        = getFloat("LapDeltaToBestLap");
    d.lapDistPct          = getFloat("LapDistPct");
    d.fuelLevel           = getFloat("FuelLevel");
    d.fuelPerLap          = getFloat("FuelUsePerHour");
    d.position            = getInt("PlayerCarPosition");
    d.sessionTimeRemaining   = getFloat("SessionTimeRemain");

    const char* tL[] = {"LFtempCL","RFtempCL","LRtempCL","RRtempCL"};
    const char* tM[] = {"LFtempCM","RFtempCM","LRtempCM","RRtempCM"};
    const char* tR[] = {"LFtempCR","RFtempCR","LRtempCR","RRtempCR"};
    for (int i = 0; i < 4; i++) {
        d.tyreTempL[i] = getFloat(tL[i]);
        d.tyreTempM[i] = getFloat(tM[i]);
        d.tyreTempR[i] = getFloat(tR[i]);
    }

    return d;
}