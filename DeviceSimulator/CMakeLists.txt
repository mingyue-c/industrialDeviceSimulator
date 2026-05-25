cmake_minimum_required(VERSION 3.16)

project(DeviceSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

qt_standard_project_setup()

qt_add_executable(DeviceSimulator
    main.cpp
    SimulatedDevice.h
    SimulatedDevice.cpp
    protocol/ProtocolBuilder.h
    protocol/ProtocolBuilder.cpp
    SimulatorServer.h
    SimulatorServer.cpp
)

target_link_libraries(DeviceSimulator
    PRIVATE
    Qt6::Core
    Qt6::Network
)