cmake_minimum_required(VERSION 3.25)
project(RacingManager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(RacingManager
        src/main.cpp
        src/iracing/IRacingReader.cpp
        src/overlay/OverlayWindow.cpp
        src/overlay/panels/StintPanel.cpp
        src/overlay/panels/DeltaPanel.cpp
        src/overlay/panels/TyrePanel.cpp
        src/core/TelemetryPoller.cpp
        SDK/irsdk/irsdk_client.cpp
        SDK/irsdk/irsdk_utils.cpp
        SDK/irsdk/yaml_parser.cpp
)

target_link_libraries(RacingManager
        Qt6::Widgets
)

target_include_directories(RacingManager PRIVATE
        SDK/irsdk
        src
)
