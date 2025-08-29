cmake_minimum_required(VERSION 3.10)
project(SystemMonitor)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

configure_file(config/config.ini config/config.ini COPYONLY)

add_executable(monitor
    src/main.cpp
    src/SystemMonitor.cpp
    src/utils/DataUtils.cpp
    src/utils/UdpSocketManager.cpp
    src/utils/ConfigManager.cpp
)