cmake_minimum_required(VERSION 4.2)
project(RacingManager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

#Iracing SDK headers
include_directories(${CMAKE_SOURCE_DIR}/SDK/irsdk)

add_executable(RacingManager src/main.cpp
        src/iracing/IRacingReader.cpp
        src/iracing/IRacingReader.h
        src/iracing/TelemetryData.h
        src/overlay/OverlayWindow.cpp
        src/overlay/OverlayWindow.h
        src/overlay/panels/StintPanel.cpp
        src/overlay/panels/StintPanel.h
        src/overlay/panels/DeltaPanel.cpp
        src/overlay/panels/DeltaPanel.h
        src/overlay/panels/TyrePanel.cpp
        src/overlay/panels/TyrePanel.h
        src/core/TelemetryPoller.cpp
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/core/TelemetryPoller.h
        src/iracing/TelemetryData.h
        src/iracing/TelemetryData.h
        src/iracing/TelemetryData.h
        src/iracing/IRacingReader.h
)

target_link_libraries(RacingManager
    Qt6::Widgets
)